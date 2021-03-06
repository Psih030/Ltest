// Ltest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
using namespace std;

const int milisecs = 1000;

class TrafficLight {

  private:
    enum LightColor { RED = 12, YELLOW = 14, GREEN = 10, WHITE = 15 };

    bool red_;
    bool yellow_;
    bool green_;

    int redDuration_;
    int yellowDuration_;
    int greenDuration_;

	int yellowBlinkCounter_;
	int yellowBlinkMax_;
	double yellowBlinkFrequency_;


  public:
    TrafficLight();

    void setRed(bool);
    void setYellow(bool);
    void setGreen(bool);
    void setRedDuration(int);
    void setYellowDuration(int);
    void setGreenDuration(int);
	void setYellowBlinkCounter(int);
	void setYellowBlinkMax(int);
	void setYellowBlinkFrequency(double);

    bool getRed();
    bool getYellow();
    bool getGreen();
    int getRedDuration();
    int getYellowDuration();
    int getGreenDuration();
	int getYellowBlinkCounter();
	int getYellowBlinkMax();
	double getYellowBlinkFrequency();

	void printCurrentState();
	void printTraficSignal(LightColor, LightColor, LightColor);
    void cycle();
};

//start of sets
void TrafficLight::setRed(bool red) { red_ = red; }
void TrafficLight::setYellow(bool yellow) { yellow_ = yellow; };
void TrafficLight::setGreen(bool green) { green_ = green; }
void TrafficLight::setRedDuration(int redDuration) { redDuration_ = redDuration; }
void TrafficLight::setYellowDuration(int yellowDuration) { yellowDuration_ = yellowDuration; }
void TrafficLight::setGreenDuration(int greenDuration) { greenDuration_ = greenDuration; }
void TrafficLight::setYellowBlinkCounter(int yellowBlinkCounter) { yellowBlinkCounter_ = yellowBlinkCounter; }
void TrafficLight::setYellowBlinkMax(int yellowBlinkMax) {yellowBlinkMax_ = yellowBlinkMax;}
void TrafficLight::setYellowBlinkFrequency(double yellowBlinkFrequency) { yellowBlinkFrequency_ = yellowBlinkFrequency; }
//end of sets


//start of gets
bool TrafficLight::getRed() { return red_; }
bool TrafficLight::getYellow() { return yellow_; }
bool TrafficLight::getGreen() { return green_; }
int TrafficLight::getRedDuration() { return redDuration_; }
int TrafficLight::getYellowDuration() { return yellowDuration_; }
int TrafficLight::getGreenDuration() { return greenDuration_; }
int TrafficLight::getYellowBlinkCounter() { return yellowBlinkCounter_; }
int TrafficLight::getYellowBlinkMax() { return yellowBlinkMax_; }
double TrafficLight::getYellowBlinkFrequency() { return yellowBlinkFrequency_; }
//end of gets

TrafficLight::TrafficLight() {
  red_ = true;
  yellow_ = false;
  green_ = false;
  redDuration_ = 2;
  yellowDuration_ = 4;
  greenDuration_ = 3;
  yellowBlinkCounter_ = 0;
  yellowBlinkMax_ = 9; 
  yellowBlinkFrequency_ = (double) yellowDuration_ / yellowBlinkMax_ ;
}


void TrafficLight::cycle()
{
	if (red_ == true) { red_ = false; yellow_ = true; }
	else if ((yellow_ == true) 
		&& (yellowBlinkCounter_ % 2 == 0) 
		&& (yellowBlinkCounter_ < yellowBlinkMax_-1)) 
	{ 
		yellow_ = false; ++yellowBlinkCounter_;
	}
	else if ((yellow_ == false) 
		&& (yellowBlinkCounter_ % 2 == 1) 
		&& (yellowBlinkCounter_ < yellowBlinkMax_-1)) 
	{ 
		yellow_ = true; ++yellowBlinkCounter_;
	}
	else if (yellowBlinkCounter_ == yellowBlinkMax_ - 1) 
	{ 
		yellow_ = false; green_ = true; yellowBlinkCounter_ = 0;
	}
	else if (green_ == true) { green_ = false; red_ = true; }
}

void TrafficLight::printTraficSignal(LightColor forRed, LightColor forYellow, LightColor forGreen)
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	cout <<  "   ___" << endl << "  | ";
	SetConsoleTextAttribute(color, forRed); cout << "o";
	SetConsoleTextAttribute(color, LightColor::WHITE);
	cout << " |" << endl << "  | ";
	SetConsoleTextAttribute(color, forYellow); cout << "o";
	SetConsoleTextAttribute(color, LightColor::WHITE);
	cout << " |" << endl << "  | ";
	SetConsoleTextAttribute(color, forGreen); cout << "o";
	SetConsoleTextAttribute(color, LightColor::WHITE);
	cout << " |" << endl << "  |___|" << endl;
}

void TrafficLight::printCurrentState()
{
	if (red_ == true) 
		printTraficSignal(LightColor::RED, LightColor::WHITE, LightColor::WHITE);
	else if (yellow_ == true) 
		printTraficSignal(LightColor::WHITE, LightColor::YELLOW, LightColor::WHITE);
	else if (green_ == true) 
		printTraficSignal(LightColor::WHITE, LightColor::WHITE, LightColor::GREEN);
	else 
		printTraficSignal(LightColor::WHITE, LightColor::WHITE, LightColor::WHITE);
}



void clearScreen();
void pause(double);



int main()
{
	
	TrafficLight myTraficLight;

	while (true)
	{
		myTraficLight.printCurrentState();
		pause(myTraficLight.getRedDuration());
		clearScreen();
		myTraficLight.cycle();
		for (int k = 0; k < myTraficLight.getYellowBlinkMax(); k++)
		{
			myTraficLight.printCurrentState();
			pause(myTraficLight.getYellowBlinkFrequency());
			clearScreen();
			myTraficLight.cycle();
		}
		myTraficLight.printCurrentState();
		pause(myTraficLight.getGreenDuration());
		clearScreen();
		myTraficLight.cycle();
	}
    return 0;
}

void pause(double secs)
{
	clock_t wait = (int)floor(secs * milisecs) + clock();
	clock_t waittimeleft = 0;

	while (wait > clock())
	{
		if (GetKeyState('E') & 0x8000)
		{
			ExitProcess(0);
		}
		else if (GetKeyState('P') & 0x8000)
		{
			if (waittimeleft == 0)
			    waittimeleft = wait - clock();
			
		}
		else if (GetKeyState('S') & 0x8000)
		{
			if (waittimeleft != 0)
			{
				wait = clock() + waittimeleft;
				waittimeleft = 0;
			}
		}
		if (waittimeleft != 0 && (wait - clock()) <= waittimeleft)
		{
			wait = wait + waittimeleft;
		}
		continue;
	}
}


void clearScreen()
{
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(
		hOut, (TCHAR) ' ', cellCount, homeCoords, &count)) return;

	if (!FillConsoleOutputAttribute(
		hOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;

	SetConsoleCursorPosition(hOut, homeCoords);
}