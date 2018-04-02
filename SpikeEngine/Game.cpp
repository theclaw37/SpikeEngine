#include "Game.h"
#include "SpikeConfig.h"

std::string test;
SpikeUI::Containers::Point point(0, 0);

SpikeEngine::Game::Game() : GameState(GameState::Initial)
{}

void SpikeEngine::Game::SetErrorState()
{
	GameState = GameState::Destroyed;
}

void SpikeEngine::Game::LoadUI(std::string const & path)
{
	//TODO: load UI config from file	
	GameUI.Init(SpikeUI::Containers::Rectangle(
		0, 0,
		SpikeConfig::Config::Instance().GetWindow().GetClientWidth(),
		SpikeConfig::Config::Instance().GetWindow().GetClientHeight()
	));

	SpikeUI::Controls::Label textArea_title(
		SpikeUI::Containers::Rectangle(30, 30, 230, 80),
		SpikeUI::Containers::Font("Arial", 25),
		SpikeUI::Colour::Colour(1.0, 1.0, 1.0));
	textArea_title.Text = "SpikeEngine";
	textArea_title.DHit = SpikeUI::UI::DrawableHit::Enable;

	SpikeUI::Controls::Button button1(
		SpikeUI::Containers::Rectangle(30, 100, 230, 150),
		SpikeUI::Colour::Colour(0.5, 0.5, 0.5));
	SpikeUI::Controls::Label button1_text(
		SpikeUI::Containers::Rectangle(30, 100, 230, 150),
		SpikeUI::Containers::Font("Arial", 25),
		SpikeUI::Colour::Colour(0.0, 0.0, 0.0));
	button1_text.Text = "New Game";

	SpikeUI::Controls::Button button2(
		SpikeUI::Containers::Rectangle(30, 200, 230, 250),
		SpikeUI::Colour::Colour(0.5, 0.5, 0.5));
	SpikeUI::Controls::Label button2_text(
		SpikeUI::Containers::Rectangle(30, 200, 230, 250),
		SpikeUI::Containers::Font("Arial", 25),
		SpikeUI::Colour::Colour(0.0, 0.0, 0.0));
	button2_text.Text = "Options";

	SpikeUI::Controls::Button button3(
		SpikeUI::Containers::Rectangle(30, 300, 230, 350),
		SpikeUI::Colour::Colour(0.5, 0.5, 0.5));
	SpikeUI::Controls::Label button3_text(
		SpikeUI::Containers::Rectangle(30, 300, 230, 350),
		SpikeUI::Containers::Font("Arial", 25),
		SpikeUI::Colour::Colour(0.0, 0.0, 0.0));
	button3_text.Text = "Help";

	SpikeUI::Controls::Button button4(
		SpikeUI::Containers::Rectangle(30, 400, 230, 450),
		SpikeUI::Colour::Colour(0.5, 0.5, 0.5));
	SpikeUI::Controls::Label button4_text(
		SpikeUI::Containers::Rectangle(30, 400, 230, 450),
		SpikeUI::Containers::Font("Arial", 25),
		SpikeUI::Colour::Colour(0.0, 0.0, 0.0));
	button4_text.Text = "Quit";


	auto hoverIn = [](SpikeUI::Controls::Label& ref)
	{
		ref.Colour = SpikeUI::Colour::Colour(0.0, 0.0, 0.0);
	};
	auto hoverOut = [](SpikeUI::Controls::Label& ref)
	{
		ref.Colour = SpikeUI::Colour::Colour(1.0, 1.0, 1.0);
	};
	auto lClickDown = [](SpikeUI::Controls::Label& ref)
	{
	};
	auto lClickUp = [](SpikeUI::Controls::Label& ref)
	{
	};

	auto hoverInBLOL = [this](SpikeUI::Controls::Button& ref)
	{
		GameUI.MoveTo(
			GameUI.Get(ref._SpikeEngineId()),
			SpikeUI::Containers::Point((rand() %  100) / 100.0, (rand() % 100) / 100.0));
	};

	auto hoverInB = [](SpikeUI::Controls::Button& ref)
	{
		ref.Colour = SpikeUI::Colour::Colour(1.0, 1.0, 1.0);
	};
	auto hoverOutB = [](SpikeUI::Controls::Button& ref)
	{
		ref.Colour = SpikeUI::Colour::Colour(0.5, 0.5, 0.5);
	};
	auto lClickDownB = [](SpikeUI::Controls::Button& ref)
	{
	};
	auto lClickUpB = [](SpikeUI::Controls::Button& ref)
	{
	};

	auto lClickUpBQuit = [](SpikeUI::Controls::Button& ref)
	{
		PostQuitMessage(0);
	};

	textArea_title.receiveFocus = hoverIn;
	textArea_title.loseFocus = hoverOut;
	textArea_title.lClickDown = lClickDown;
	textArea_title.lClickUp = lClickUp;

	button1.receiveFocus = hoverInBLOL;
	button1.loseFocus = hoverOutB;
	button1.lClickDown = lClickDownB;
	button1.lClickUp = lClickUpB;

	button2.receiveFocus = hoverInB;
	button2.loseFocus = hoverOutB;
	button2.lClickDown = lClickDownB;
	button2.lClickUp = lClickUpB;

	button3.receiveFocus = hoverInB;
	button3.loseFocus = hoverOutB;
	button3.lClickDown = lClickDownB;
	button3.lClickUp = lClickUpB;

	button4.receiveFocus = hoverInB;
	button4.loseFocus = hoverOutB;
	button4.lClickDown = lClickDownB;
	button4.lClickUp = lClickUpBQuit;

	GameUI.Insert(textArea_title, SpikeUI::UI::Front);
	GameUI.Insert(button1, SpikeUI::UI::Front);
	GameUI.Insert(button2, SpikeUI::UI::Front);
	GameUI.Insert(button3, SpikeUI::UI::Front);
	GameUI.Insert(button4, SpikeUI::UI::Front);
	GameUI.Insert(button1_text, button1._SpikeEngineId(), SpikeUI::UI::Front);
	GameUI.Insert(button2_text, button2._SpikeEngineId(), SpikeUI::UI::Front);
	GameUI.Insert(button3_text, button3._SpikeEngineId(), SpikeUI::UI::Front);
	GameUI.Insert(button4_text, button4._SpikeEngineId(), SpikeUI::UI::Front);

	test = button1._SpikeEngineId();
}

#ifdef _WIN32
void SpikeEngine::Game::LoadRenderer(HWND hwnd)
{
	GameRenderer.InitRenderer(
		hwnd,
		SpikeConfig::Config::Instance().GetWindow().GetClientWidth(),
		SpikeConfig::Config::Instance().GetWindow().GetClientHeight());
}
#endif

void SpikeEngine::Game::Frame(float deltaTime)
{
	GameRenderer.RenderFrame(0.0, 0.0, 0.0);
	GameRenderer.RenderUI(GameUI);
	GameRenderer.PresentToScreen();
}

void SpikeEngine::Game::Update(float deltaTime)
{
}


SpikeEngine::GameState SpikeEngine::Game::GetState()
{
	if (GameState == GameState::Initial)
	{
		if (GameUI.GetState() > SpikeUI::UI::UIState::Initial ||
			GameRenderer.GetState() > SpikeRenderer::RendererState::Initial)
		{
			GameState = GameState::Loading;
		}

		if (GameUI.GetState() > SpikeUI::UI::UIState::Initial &&
			GameRenderer.GetState() > SpikeRenderer::RendererState::Initial)
		{
			GameState = GameState::Loaded;
		}
	}

	return GameState;
}

SpikeEngine::Game::~Game()
{
	GameRenderer.ShutdownRenderer();
}

