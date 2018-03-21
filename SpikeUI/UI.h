#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "Drawable.h"
#include "TextArea.h"

namespace SpikeUI
{
	namespace UI
	{
		class __declspec(dllexport) UI
		{
		public:
			UI() = default;

			template<typename T>
		    void Insert(T const &);
			void Erase(std::string const &);

			void Iterate(
				std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)>);

			std::shared_ptr<SpikeUI::UI::Drawable> Mouse(
				SpikeUI::Containers::Point,
				bool,
				bool);

			
		private:
			std::vector<std::shared_ptr<SpikeUI::UI::Drawable>> UIContainer;
			std::shared_ptr<SpikeUI::UI::Drawable> UIFocus;

			void SwitchFocus(std::shared_ptr<SpikeUI::UI::Drawable> target);
		};

		template<typename T>
		inline void UI::Insert(T const & drawable)
		{
			UIContainer.push_back(std::make_shared<T>(drawable));
		}
	}
}