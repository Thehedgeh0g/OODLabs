#include <cmath>
#include <iostream>
#include <sstream>

#include "ImageService.h"
#include "src/Drawer.h"

constexpr int STAR_COUNT = 20;

int main()
{
	{
		Image img = ImageService::LoadImage(
				"......................,,uod8B8bou,,...............................\n"
"..............,,uod8BBBBBBBBBBBBBBBBRPFT?l!i:.....................\n"
".........,=m8BBBBBBBBBBBBBBBRPFT?!||||||||||||||..................\n"
".........!...:!TVBBBRPFT||||||||||!!^^""'.....||||..................\n"
".........!.......:!?|||||!!^^""'..............||||..................\n"
".........!.........||||.....................||||..................\n"
".........!.........||||..##.................||||..................\n"
".........!.........||||.....................||||..................\n"
".........!.........||||.....................||||..................\n"
".........!.........||||.....................||||..................\n"
".........!.........||||.....................||||..................\n"
".........`.........||||....................,||||..................\n"
"..........;........||||.............._.-!!|||||...................\n"
"....,uodWBBBBb.....||||......._.-!!|||||||||!:'...................\n"
".!YBBBBBBBBBBBBBBb..!|||:..-!!|||||||!iof68BBBBBb.................\n"
"..!..YBBBBBBBBBBBBBBb!!||||||||!iof68BBBBBBRPFT?!::...`...........\n"
".!....YBBBBBBBBBBBBBBbaaitf68BBBBBBRPFT?!:::::::::.....`..........\n"
".!......YBBBBBBBBBBBBBBBBBBBRPFT?!::::::;:!^\"`;:::......`.........\n"
".!........YBBBBBBBBBBRPFT?!::::::::::^''...::::::;.......iBBbo....\n"
".`..........YBRPFT?!::::::::::::::::::::::::;iof68bo.....WBBBBbo..\n"
"...`..........:::::::::::::::::::::::;iof688888888888b....`YBBBP^'\n"
".....`........::::::::::::::::;iof688888888888888888888b..........\n"
".......`......:::::::::;iof688888888888888888888888888888b........\n"
".........`....:::;iof688888888888888888888888888888888899fT!......\n"
"...........`..::!8888888888888888888888888888888899fT|!^\"'........\n"
".............`'..!!988888888888888888888888899fT|!^\"'.............\n"
".................`!!8888888888888888899fT|!^\"'....................\n"
"...................`!988888888899fT|!^\"'..........................\n"
".....................`!9899fT|!^\"'................................\n"
".......................`!^\"'......................................\n");
		ImageService::Print(img, std::cout);
	}

	int mode;
	std::string outFile;
	uint32_t backgroundColor = '.';
	uint32_t lineColor = '@';
	uint32_t circleColor = '#';
	while (true)
	{
		std::cout << "Please choose mode: \n - 1 write into console\n - 2 write into file\n";
		if (!(std::cin >> mode))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input! Please enter a number.\n";
			continue;
		}

		if (mode == 2)
		{
			std::cout << "Please enter filename\n";
			std::cin >> outFile;
			backgroundColor = 0xFFFFFF;
			lineColor = 0x00FF00;
			circleColor = 0x00FFBB;
			break;
		}
		if (mode == 1)
		{
			break;
		}
		std::cout << "Wrong print mode! Please enter 1 or 2.\n";
	}
	Image img({80, 50}, backgroundColor);

	Drawer::DrawCircle(img, {19, 19}, 2, lineColor);
	Drawer::DrawLine(img, {18, 22}, {20, 25}, lineColor);
	Drawer::DrawLine(img, {20, 25}, {50, 17}, lineColor);
	Drawer::DrawLine(img, {50, 17}, {24, 21}, lineColor);
	Drawer::DrawLine(img, {24, 21}, {22, 20}, lineColor);
	Drawer::DrawFilledCircle(img, {15, 13}, 3, circleColor);
	Drawer::DrawFilledCircle(img, {14, 10}, 4, circleColor);
	Drawer::DrawFilledCircle(img, {14, 8}, 5, circleColor);
	//Drawer::DrawLine(img, {35, 17}, {25, 20}, lineColor);
	//Drawer::DrawLine(img, {15, 18}, {25, 18}, lineColor);

	//Drawer::DrawLine(img, {5, 8}, {5, 18}, lineColor);
	//Drawer::DrawLine(img, {25, 8}, {25, 18}, lineColor);
	//Drawer::DrawLine(img, {5, 18}, {25, 18}, lineColor);

	//Drawer::DrawLine(img, {5, 8}, {15, 1}, lineColor);
	//Drawer::DrawLine(img, {15, 1}, {25, 8}, lineColor);
	//Drawer::DrawLine(img, {5, 8}, {25, 8}, lineColor);

	//Drawer::DrawLine(img, {5, 8}, {5, 18}, lineColor);
	//Drawer::DrawLine(img, {25, 8}, {25, 18}, lineColor);
	//Drawer::DrawLine(img, {5, 18}, {25, 18}, lineColor);

	//Drawer::DrawFilledCircle(img, {15, 13}, 4, circleColor);


	if (mode == 1)
	{
		ImageService::Print(img, std::cout);
	}
	else if (mode == 2)
	{
		ImageService::SaveToPPM(outFile, img);
	}

	return 0;
}
