#include "Game.h"
#include "SpikeConfig.h"

SpikeEngine::Game::Game() : GameState(GameState::Initial)
{}

void SpikeEngine::Game::SetErrorState()
{
	GameState = GameState::Destroyed;
}

void SpikeEngine::Game::LoadConfig(std::string const & path)
{
	if (GameState != GameState::Unloading)
	{
		SpikeConfig::Config::Instance().Load(path);
	}
}

#ifdef _WIN32
void SpikeEngine::Game::LoadRenderer(HWND hWnd)
{
	if (GameState != GameState::Unloading)
	{
		Objects.GameRenderer.InitRenderer(
			hWnd,
			SpikeConfig::Config::Instance().GetWindow().GetClientWidth(),
			SpikeConfig::Config::Instance().GetWindow().GetClientHeight());
	}
}
#endif

void SpikeEngine::Game::LoadUI()
{
	if (GameState != GameState::Unloading)
	{
		//TODO: load UI config from file	
		Objects.GameUI.Init(SpikeUI::Containers::Rectangle(
			0, 0,
			SpikeConfig::Config::Instance().GetWindow().GetClientWidth(),
			SpikeConfig::Config::Instance().GetWindow().GetClientHeight()
		));

		SpikeUI::Controls::Label textArea_title(
			SpikeUI::Containers::Rectangle(0.1, 0.1, 0.4, 0.25),
			SpikeUI::Containers::Font("Arial", 25),
			SpikeUI::Colour::Colour(1.0, 1.0, 1.0));
		textArea_title.Text = "Test Label with Hover enable";
		textArea_title.DHit = SpikeUI::UI::DrawableHit::Enable;

		SpikeUI::Controls::Button button1(
			SpikeUI::Containers::Rectangle(0.1, 0.3, 0.4, 0.45),
			SpikeUI::Colour::Colour(0.5, 0.5, 0.5));
		SpikeUI::Controls::Label button1_text(
			SpikeUI::Containers::Rectangle(0.0, 0.0, 100.0, 100.0),
			SpikeUI::Containers::Font("Arial", 25),
			SpikeUI::Colour::Colour(0.0, 0.0, 0.0));
		button1_text.Text = "Test Button with Hover enable";

		SpikeUI::Controls::Button button4(
			SpikeUI::Containers::Rectangle(0.1, 0.5, 0.4, 0.65),
			SpikeUI::Colour::Colour(0.5, 0.5, 0.5));
		SpikeUI::Controls::Label button4_text(
			SpikeUI::Containers::Rectangle(0.0, 0.0, 100.0, 100.0),
			SpikeUI::Containers::Font("Arial", 25),
			SpikeUI::Colour::Colour(0.0, 0.0, 0.0));
		button4_text.Text = "Test Button with Action (QUIT)";

		SpikeUI::Controls::Button button_test(
			SpikeUI::Containers::Rectangle(0.1, 0.7, 0.4, 0.85),
			SpikeUI::Colour::Colour(0.5, 0.5, 0.5));
		SpikeUI::Controls::Button button_test_subbutton(
			SpikeUI::Containers::Rectangle(0.25, 0.25, 0.75, 0.75),
			SpikeUI::Colour::Colour(1.0, 0.0, 0.0));
		SpikeUI::Controls::Label button_test_subbutton_label(
			SpikeUI::Containers::Rectangle(0.0, 0.0, 100.0, 100.0),
			SpikeUI::Containers::Font("Arial", 15),
			SpikeUI::Colour::Colour(1.0, 1.0, 1.0));
		button_test_subbutton_label.Text = "Test Nested bounds";
		button_test_subbutton_label.DHit = SpikeUI::UI::DrawableHit::Disable;

		SpikeUI::Controls::Progress prog_bar({ 0.1, 0.9, 0.9, 0.95 },
		{ 0.0, 1.0, 0.0 },
		{ 0.5, 0.5, 0.5 }
		);

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
			Objects.GameUI.MoveTo(
				Objects.GameUI.Get(ref._SpikeEngineId()),
				SpikeUI::Containers::Point((rand() % 100 / 100.0), (rand() % 100 / 100.0)));
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
		auto lClickUpB = [this, prog_bar](SpikeUI::Controls::Button& ref)
		{
			auto pr_bar = Objects.GameUI.Get(prog_bar._SpikeEngineId());
			auto bar = std::static_pointer_cast<SpikeUI::Controls::Progress>(pr_bar);
			bar->IncreaseProgress(0.1);
		};

		auto lClickUpBQuit = [](SpikeUI::Controls::Button& ref)
		{
			PostQuitMessage(0);
		};

		textArea_title.receiveFocus = hoverIn;
		textArea_title.loseFocus = hoverOut;
		textArea_title.lClickDown = lClickDown;
		textArea_title.lClickUp = lClickUp;

		button1.receiveFocus = hoverInB;
		button1.loseFocus = hoverOutB;
		button1.lClickDown = lClickDownB;
		button1.lClickUp = lClickUpB;

		button4.receiveFocus = hoverInB;
		button4.loseFocus = hoverOutB;
		button4.lClickDown = lClickDownB;
		button4.lClickUp = lClickUpBQuit;

		button_test.receiveFocus = hoverInB;
		button_test.loseFocus = hoverOutB;
		button_test_subbutton.receiveFocus = hoverInBLOL;

		Objects.GameUI.Insert(textArea_title, SpikeUI::UI::Front);
		Objects.GameUI.Insert(button1, SpikeUI::UI::Front);
		Objects.GameUI.Insert(button4, SpikeUI::UI::Front);
		Objects.GameUI.Insert(button1_text, button1._SpikeEngineId(), SpikeUI::UI::Front);
		Objects.GameUI.Insert(button4_text, button4._SpikeEngineId(), SpikeUI::UI::Front);
		Objects.GameUI.Insert(button_test, SpikeUI::UI::Front);
		Objects.GameUI.Insert(button_test_subbutton, button_test._SpikeEngineId(), SpikeUI::UI::Front);
		Objects.GameUI.Insert(button_test_subbutton_label, button_test_subbutton._SpikeEngineId(), SpikeUI::UI::Front);
		Objects.GameUI.Insert(prog_bar, SpikeUI::UI::Front);
	}
}

void SpikeEngine::Game::Frame(float deltaTime)
{
	if (GameState >= GameState::Loaded && GameState != GameState::Unloading)
	{
		Objects.GameRenderer.RenderFrame(0.0, 0.0, 0.0);
		Objects.GameRenderer.RenderUI(Objects.GameUI);
		Objects.GameRenderer.PresentToScreen();
	}
}

void SpikeEngine::Game::Update(float deltaTime)
{
	if (GameState >= GameState::Loaded && GameState != GameState::Unloading)
	{
		//TODO: Do update
	}
}

SpikeEngine::GameState SpikeEngine::Game::GetState()
{
	if (GameState == GameState::Initial)
	{
		if (SpikeConfig::Config::Instance().GetState() ==SpikeConfig::ConfigState::Loaded &&
			(Objects.GameUI.GetState() > SpikeUI::UI::UIState::Initial ||
			Objects.GameRenderer.GetState() > SpikeRenderer::RendererState::Initial))
		{
			GameState = GameState::Loading;
		}

		if (SpikeConfig::Config::Instance().GetState() == SpikeConfig::ConfigState::Loaded &&
			(Objects.GameUI.GetState() > SpikeUI::UI::UIState::Initial &&
			Objects.GameRenderer.GetState() > SpikeRenderer::RendererState::Initial))
		{
			GameState = GameState::Loaded;
		}
	}

	return GameState;
}

SpikeEngine::Game::~Game()
{
	Objects.GameRenderer.ShutdownRenderer();
}

