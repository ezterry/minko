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

#include "minko/file/FileProtocolWorker.hpp"

using namespace minko;
using namespace minko::file;

namespace minko
{
    namespace file
    {
        MINKO_DEFINE_WORKER(FileProtocolWorker,
        {
//#ifdef DEBUG
            std::cout << "FileProtocolWorker::run(): enter" << std::endl;
//#endif // defined(DEBUG)

            std::string filename(input.begin(), input.end());

            std::vector<char> output;

            post(Message { "progress" }.set(0.0f));

            auto flags = std::ios::in | std::ios::ate | std::ios::binary;

            std::fstream file(filename, flags);

            if (file.is_open())
            {
                uint size = uint(file.tellg());

                uint chunkSize = math::clp2((size / 50) / 1024);

                if (chunkSize > 1024)
                    chunkSize = 1024;
                else if (chunkSize <= 0)
                    chunkSize = 8;

                chunkSize *= 1024;

//#ifdef DEBUG
                std::cout << "FileProtocolWorker::run(): file is open, chunksize " + std::to_string(chunkSize) << std::endl;
//#endif // defined(DEBUG)

                file.seekg(0, std::ios::beg);

                uint offset = 0;

                while (offset < size)
                {
                    uint nextOffset = offset + chunkSize;
                    uint readSize = chunkSize;

                    if (nextOffset > size)
                        readSize = size % chunkSize;

                    output.resize(offset + readSize);

                    file.read(&*output.begin() + offset, readSize);

                    post(Message { "progress" }.set(float(offset + readSize) / float(size)));

                    offset = nextOffset;
                }

                file.close();

                post(Message{ "complete" }.set(output));
            }
            else
            {
                post(Message{ "error" });
            }

//#ifdef DEBUG
            std::cout << "FileProtocolWorker::run(): exit" << std::endl;
//#endif // defined(DEBUG)
        });
    }
}
