#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
#include "Drawable.h"
#include "Rectangle.h"

namespace SpikeUI
{
	namespace UI
	{
		enum UIOrder
		{
			Front = 1,
			Back = 2
		};

		class __declspec(dllexport) UI
		{
		public:
			UI(SpikeUI::Containers::Rectangle const &);
			
			template <typename T>
			void Insert(T const &, UIOrder const &);
			template <typename T>
			void Insert(T const &, std::string const &, UIOrder const &);
			void Erase(std::string const &);
			std::shared_ptr<SpikeUI::UI::Drawable> Get(std::string const &);

			void IterateBackToFront(
				std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)>);
			void IterateFrontToBack(
				std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)>);

			void Update(
				SpikeUI::Containers::Point const &,
				bool,
				bool);

			
		private:
			std::shared_ptr<SpikeUI::UI::Drawable> UIRoot;
			std::shared_ptr<SpikeUI::UI::Drawable> UIFocus;
			std::unordered_map<std::string, std::shared_ptr<SpikeUI::UI::Drawable>> UIElems;

			void SwitchFocus(std::shared_ptr<SpikeUI::UI::Drawable>);
			void Erase(std::shared_ptr<SpikeUI::UI::Drawable>, std::string const &);
			void IterateBackToFront(
				std::shared_ptr<SpikeUI::UI::Drawable>,
				std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)>);
			void IterateFrontToBack(
				std::shared_ptr<SpikeUI::UI::Drawable>,
				std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)>);
		};

		template<typename T>
		inline void UI::Insert(
			T const & drawable, 
			UIOrder const & order)
		{
			auto ptr = std::make_shared<T>(drawable);
			UIElems.insert({
				ptr->_SpikeEngineId(),
				ptr });

			if (order == UIOrder::Front)
				UIRoot->DChildren.push_back(ptr);
			else if (order == UIOrder::Back)
				UIRoot->DChildren.push_front(ptr);
		}

		template<typename T>
		inline void UI::Insert(
			T const & drawable, 
			std::string const & guid, 
			UIOrder const & order)
		{
			auto ptr = std::make_shared<T>(drawable);
			UIElems.insert({
				ptr->_SpikeEngineId(),
				ptr });

			auto parent = Get(guid);
			if (parent)
			{
				if (order == UIOrder::Front)
					parent->DChildren.push_back(ptr);
				else if (order == UIOrder::Back)
					parent->DChildren.push_front(ptr);
			}
		}
	}
}