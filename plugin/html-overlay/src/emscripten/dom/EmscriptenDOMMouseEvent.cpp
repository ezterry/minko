/*
Copyright (c) 2013 Aerys

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

#include "minko/Common.hpp"
#include "emscripten/dom/EmscriptenDOMMouseEvent.hpp"
#include "emscripten/dom/EmscriptenDOMElement.hpp"
#include "emscripten/emscripten.h"

using namespace minko;
using namespace minko::dom;
using namespace emscripten;
using namespace emscripten::dom;

int
EmscriptenDOMMouseEvent::clientX()
{
	std::string eval = "(" + _jsAccessor + ".clientX)";
	int result = emscripten_run_script_int(eval.c_str());
	return result;
}

int
EmscriptenDOMMouseEvent::clientY()
{
	std::string eval = "(" + _jsAccessor + ".clientY)";
	int result = emscripten_run_script_int(eval.c_str());
	return result;
}

int
EmscriptenDOMMouseEvent::pageX()
{
	std::string eval = "(" + _jsAccessor + ".pageX)";
	int result = emscripten_run_script_int(eval.c_str());
	return result;
}

int
EmscriptenDOMMouseEvent::pageY()
{
	std::string eval = "(" + _jsAccessor + ".pageY)";
	int result = emscripten_run_script_int(eval.c_str());
	return result;
}

int
EmscriptenDOMMouseEvent::layerX()
{
	std::string eval = "(" + _jsAccessor + ".layerX)";
	int result = emscripten_run_script_int(eval.c_str());
	return result;
}

int
EmscriptenDOMMouseEvent::layerY()
{
	std::string eval = "(" + _jsAccessor + ".layerY)";
	int result = emscripten_run_script_int(eval.c_str());
	return result;
}

int
EmscriptenDOMMouseEvent::screenX()
{
	std::string eval = "(" + _jsAccessor + ".screenX)";
	int result = emscripten_run_script_int(eval.c_str());
	return result;
}

int
EmscriptenDOMMouseEvent::screenY()
{
	std::string eval = "(" + _jsAccessor + ".screenY)";
	int result = emscripten_run_script_int(eval.c_str());
	return result;
}
