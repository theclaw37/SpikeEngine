#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
#include "Drawable.h"
#include "Rectangle.h"
#include "Key.h"

#ifdef DLL_SPIKEUI
#define SPIKEUI_EXPORT __declspec(dllexport)
#else
#define SPIKEUI_EXPORT __declspec(dllimport)
#endif

namespace SpikeUI
{
	namespace UI
	{
		enum UIOrder
		{
			Front = 1,
			Back = 2
		};

		enum UIState
		{
			Initial = 0,
			Ready = 1
		};

		class SPIKEUI_EXPORT UI
		{
		public:
			UI();

			void Init(SpikeUI::Containers::Rectangle const &);
			
			template <typename T>
			void Insert(T const &, UIOrder const &);
			template <typename T>
			void Insert(T const &, std::string const &, UIOrder const &);
			void Erase(std::string const &);
			std::shared_ptr<SpikeUI::UI::Drawable> Get(std::string const &);
			void MoveTo(std::shared_ptr<SpikeUI::UI::Drawable>, SpikeUI::Containers::Point const &);
			void MoveBy(std::shared_ptr<SpikeUI::UI::Drawable>, SpikeUI::Containers::Point const &);

			void IterateBackToFront(
				std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)>);
			void IterateFrontToBack(
				std::function<void(std::shared_ptr<SpikeUI::UI::Drawable>)>);

			void UpdateForPointer(
				SpikeUI::Containers::Point const &,
				bool,
				bool);

			void UpdateForKey(
				SpikeUI::Containers::Key const &);

			UIState GetState() const;

		private:
			std::shared_ptr<SpikeUI::UI::Drawable> _UIRoot;
			std::shared_ptr<SpikeUI::UI::Drawable> _UIFocus;
			std::unordered_map<std::string, std::shared_ptr<SpikeUI::UI::Drawable>> _UIElems;
			UIState _UIState;

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
			ptr->DParent = _UIRoot;

			auto newTopLeft = _UIRoot->RelativePixelDelta(
				ptr->Place.TopLeft.ClampToPercentage());
			auto newBottomRight = _UIRoot->RelativePixelDelta(
				ptr->Place.BottomRight.ClampToPercentage());
			ptr->Place.TopLeft = newTopLeft;
			ptr->Place.BottomRight = newBottomRight;
			
			_UIElems.insert({
				ptr->_SpikeEngineId(),
				ptr });

			if (order == UIOrder::Front)
				_UIRoot->DChildren.push_back(ptr);
			else if (order == UIOrder::Back)
				_UIRoot->DChildren.push_front(ptr);
		}

		template<typename T>
		inline void UI::Insert(
			T const & drawable, 
			std::string const & guid, 
			UIOrder const & order)
		{
			auto parent = Get(guid);
			if (parent)
			{
				auto ptr = std::make_shared<T>(drawable);
				ptr->DParent = parent;
				
				auto newTopLeft = parent->RelativePixelDelta(
					ptr->Place.TopLeft.ClampToPercentage());
				auto newBottomRight = parent->RelativePixelDelta(
					ptr->Place.BottomRight.ClampToPercentage());

				ptr->Place.TopLeft = newTopLeft;
				ptr->Place.BottomRight = newBottomRight;

				_UIElems.insert({
					ptr->_SpikeEngineId(),
					ptr });


				if (order == UIOrder::Front)
					parent->DChildren.push_back(ptr);
				else if (order == UIOrder::Back)
					parent->DChildren.push_front(ptr);


			}
		}
	}
}