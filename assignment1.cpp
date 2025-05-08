#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

int main()
{
	// file reading
	std::ifstream dataFile("input/config.txt");
	if (!dataFile.is_open()) {
		std::cerr << "Failed to open file!" << std::endl;
		return 1;
	}

	std::string type;
	unsigned int wWidth = 1280, wHeight = 720;

	std::string fontFile;
	unsigned int fontSize = 12;
	int fontR = 0, fontG = 0, fontB = 0;
	while (dataFile >> type)
	{
		if (type == "Window")
		{
			dataFile >> wWidth >> wHeight;
		}
		else if (type == "Font")
		{
			dataFile >> fontFile >> fontSize >> fontR >> fontG >> fontB;
		}
		else if (type == "Circle")
		{

		}
		else if (type == "Rectangle")
		{

		}
	}
	dataFile.close();
	
	// init window
	sf::RenderWindow window(sf::VideoMode({ wWidth, wHeight }), "SFML works!");
	window.setFramerateLimit(60);
	if (!ImGui::SFML::Init(window))
	{
		std::cerr << "Could not initialize window!" << std::endl;
		exit(-1);
	}
	sf::Clock deltaClock;

	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui::GetIO().FontGlobalScale = 2.0f;

	// shapes input
	float c[3] = { 0.0f, 1.0f, 1.0f };

	float circleRadius = 50;
	int circleSegments = 32;
	float circleSpeedX = 1.0f;
	float circleSpeedY = 0.5f;
	bool drawCircle = true;
	bool drawText = true;

	// init position prior to game loop
	sf::CircleShape circle(circleRadius, circleSegments);
	circle.setPosition({ 10.0f, 10.0f });

	sf::Font myFont;
	if (!myFont.openFromFile(fontFile))
	{
		std::cerr << "Could not load front!" << std::endl;
		exit(-1);
	}

	char displayString[255] = "Sample Text";
	sf::Text text(myFont, displayString, fontSize);
	text.setPosition({ 0, wHeight - (float)text.getCharacterSize() });
	text.setFillColor(sf::Color(fontR, fontG, fontB));

	// game loop
	while (window.isOpen())
	{
		// user input
		while (const std::optional<sf::Event> event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, *event);
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::X)
					circleSpeedX *= -1.0f;
				else if (keyPressed->scancode == sf::Keyboard::Scancode::Y)
					circleSpeedY *= -1.0f;
			}
		}

		// imgui start
		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("Window title");
		ImGui::Text("Window text!");
		ImGui::Checkbox("Draw Circle", &drawCircle);
		ImGui::SameLine();
		ImGui::Checkbox("Draw Text", &drawText);
		ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
		ImGui::SliderInt("Sides", &circleSegments, 3, 64);
		ImGui::ColorEdit3("Color Circle", c);
		ImGui::InputText("Text", displayString, 255);
		if (ImGui::Button("Set Text"))
		{
			text.setString(displayString);
		}
		ImGui::SameLine();
		if (ImGui::Button("Reset Circle"))
		{
			circle.setPosition({ 0, 0 });
		}
		ImGui::End();
		// imgui end

		// update shapes
		circle.setRadius(circleRadius);
		circle.setPointCount(circleSegments);

		circle.setFillColor(sf::Color(std::uint8_t(c[0] * 255), std::uint8_t(c[1] * 255), std::uint8_t(c[2] * 255)));

		circle.setPosition(circle.getPosition() + sf::Vector2f(circleSpeedX, circleSpeedY));

		// draw and render
		window.clear();
		if (drawCircle)
		{
			window.draw(circle);
		}
		if (drawText)
		{
			window.draw(text);
		}
		ImGui::SFML::Render(window);
		window.display();
	}

	return 0;
}