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

#pragma once

#include "minko/Common.hpp"
#include "minko/dom/AbstractDOMElement.hpp"
#include "minko/dom/AbstractDOMTouchEvent.hpp"

namespace macwebview
{
    namespace dom
    {
        class MacWebViewDOMEngine;

        class MacWebViewDOMEvent : public virtual minko::dom::AbstractDOMEvent
        {
        public:
            typedef std::shared_ptr<MacWebViewDOMEvent> Ptr;

        protected:
            MacWebViewDOMEvent(std::string jsAccessor):
                _jsAccessor(jsAccessor)
            {
            }

        public:
            static
            Ptr
            create(std::string jsAccessor, std::shared_ptr<MacWebViewDOMEngine> engine)
            {
                Ptr event(new MacWebViewDOMEvent(jsAccessor));
                event->_engine = engine;

                return event;
            }

            void
            preventDefault();

            void
            stopPropagation();

            std::string
            type();

            minko::dom::AbstractDOMElement::Ptr
            target();

        protected:
            std::string _jsAccessor;
            std::shared_ptr<MacWebViewDOMEngine> _engine;
        };
    }
}
