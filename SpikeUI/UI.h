#pragma once

#include <vector>
#include <memory>
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
		    void Insert(T const & drawable);

			void Erase(std::string const & guid);

			void Reset();
			DrawableType GetType();

			template<class T>
			std::shared_ptr<T> Get();

			bool Iterate();

			
		private:
			std::vector<std::shared_ptr<SpikeUI::UI::Drawable>> UIContainer;
			std::vector<std::shared_ptr<SpikeUI::UI::Drawable>>::iterator UIContainerIterator;
		};

		template<typename T>
		inline void UI::Insert(T const & drawable)
		{
			UIContainer.push_back(std::make_shared<T>(drawable));
			Reset();
		}

		template<typename T>
		inline std::shared_ptr<T> UI::Get()
		{
			return std::static_pointer_cast<T>(*UIContainerIterator);
		}
	}
}