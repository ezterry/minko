/*
Copyright (c) 2014 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "minko/file/FileProtocol.hpp"

#include "minko/file/Options.hpp"
#include "minko/Signal.hpp"
#include "minko/AbstractCanvas.hpp"
#include "minko/async/Worker.hpp"

#include <fstream>
#include <regex>

using namespace minko;
using namespace minko::file;

FileProtocol::FileProtocol()
{
}

std::list<std::shared_ptr<FileProtocol>>
FileProtocol::_runningLoaders;

void
FileProtocol::load()
{
    auto loader = std::static_pointer_cast<FileProtocol>(shared_from_this());

    _runningLoaders.push_back(loader);

    auto filename = _file->filename();
    auto options = _options;
    auto flags = std::ios::in | std::ios::ate | std::ios::binary;

    std::string cleanFilename = "";

    for (uint i = 0; i < filename.length(); ++i)
    {
        if (i < filename.length() - 2 && filename.at(i) == ':' && filename.at(i + 1) == '/' && filename.at(i + 2) == '/')
        {
            cleanFilename = "";
            i += 2;
            continue;
        }

        cleanFilename += filename.at(i);
    }

    _options = options;

    auto realFilename = options->uriFunction()(File::sanitizeFilename(cleanFilename));

    std::fstream file(cleanFilename, flags);

    if (!file.is_open())
    {
        for (auto path : _options->includePaths())
        {
            const auto absolutePrefix = File::getBinaryDirectory() + "/";

            auto testFilename = options->uriFunction()(File::sanitizeFilename(path + '/' + cleanFilename));

            file.open(testFilename, flags);

            if (file.is_open())
            {
                realFilename = testFilename;
                break;
            }
        }
    }

    if (file.is_open())
    {
        resolvedFilename(realFilename);

        if (_options->loadAsynchronously() && AbstractCanvas::defaultCanvas() != nullptr
            && AbstractCanvas::defaultCanvas()->isWorkerRegistered("file-protocol"))
        {
            file.close();
            auto worker = AbstractCanvas::defaultCanvas()->getWorker("file-protocol");

            _workerSlots.push_back(worker->message()->connect([=](async::Worker::Ptr, async::Worker::Message message)
            {
                if (message.type == "complete")
                {
                    void* bytes = &*message.data.begin();
                    data().assign(static_cast<unsigned char*>(bytes), static_cast<unsigned char*>(bytes) + message.data.size());
                    _complete->execute(loader);
                    _runningLoaders.remove(loader);
                }
                else if (message.type == "progress")
                {
                    float ratio = *reinterpret_cast<float*>(&*message.data.begin());
                    _progress->execute(loader, ratio);
                }
                else if (message.type == "error")
                {
                    _error->execute(loader);
                    _runningLoaders.remove(loader);
                }
            }));

            std::vector<char> input(resolvedFilename().begin(), resolvedFilename().end());

            worker->start(input);
        }
        else
        {
            unsigned int size = (unsigned int)file.tellg();

            // FIXME: use fixed size buffers and call _progress accordingly

            _progress->execute(shared_from_this(), 0.0);

            data().resize(size);

            file.seekg(0, std::ios::beg);
            file.read((char*)&data()[0], size);
            file.close();

            _progress->execute(loader, 1.0);

            _complete->execute(shared_from_this());
            _runningLoaders.remove(loader);
        }
    }
    else
    {
        std::cout << "FileProtocol::load() : Could not load file " + filename << std::endl;
        _error->execute(shared_from_this());
    }
}
