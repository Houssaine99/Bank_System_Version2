#pragma once

#include <iostream>
#include <cstdlib>

#include "clsDate.h"

class clsUtil
{
public:

	enum enCharType { SmallLetter = 1, CapitalLetter = 2, SpecialCharacter = 3, Digit = 4, MixChars = 5 };

	enum enColor { RED = 0, GREEN = 1, YELLOW = 2, BLUE = 3, MAGENTA = 4, CYAN = 5, WHITE = 6, LIGHTGREEN = 7 };

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To)
	{
		int RandomNumber = rand() % (To - From + 1) + From;

		return RandomNumber;
	}

	static char GetRandomCharacter(enCharType CharType)
	{
		switch (CharType)
		{
		case enCharType::SmallLetter:
			return char(RandomNumber(97, 122));
		case enCharType::CapitalLetter:
			return char(RandomNumber(65, 90));
		case enCharType::SpecialCharacter:
			return char(RandomNumber(33, 47));
		case enCharType::Digit:
			return char(RandomNumber(48, 57));
		case enCharType::MixChars:
			return char(RandomNumber(33, 126));
		default:
			return '\0';
		}
	}

	static std::string GenerateWord(enCharType CharType, short Length)
	{
		std::string Word = "";

		for (int i = 0; i < Length; i++)
		{
			Word = Word + GetRandomCharacter(CharType);
		}

		return Word;
	}

	static std::string GenerateKey(enCharType CharType)
	{
		std::string Key = "";

		Key = GenerateWord(CharType, 4) + '-';
		Key = Key + GenerateWord(CharType, 4) + '-';
		Key = Key + GenerateWord(CharType, 4) + '-';
		Key = Key + GenerateWord(CharType, 4);

		return Key;
	}

	static void GenerateKeys(short NumberOfKeys, enCharType CharType)
	{
		std::cout << std::endl;

		for (int i = 1; i <= NumberOfKeys; i++)
		{
			std::cout << "Key [" << i << "] : " << GenerateKey(CharType) << std::endl;
		}
	}

	static void Swap(int& NumberA, int& NumberB)
	{
		int Temp;

		Temp = NumberA;
		NumberA = NumberB;
		NumberB = Temp;
	}

	static void Swap(double& NumberA, double& NumberB)
	{
		double Temp;

		Temp = NumberA;
		NumberA = NumberB;
		NumberB = Temp;
	}

	static  void Swap(bool& A, bool& B)
	{
		bool Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(char& A, char& B)
	{
		char Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(std::string& StringA, std::string& StringB)
	{
		std::string Temp;

		Temp = StringA;
		StringA = StringB;
		StringB = Temp;
	}

	static void Swap(clsDate& DateA, clsDate& DateB)
	{
		clsDate Temp;

		Temp = DateA;
		DateA = DateB;
		DateB = Temp;
	}

	static void ShuffleArray(int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static void ShuffleArray(std::string arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static void FillArrayWithRandomNumbers(int Arr[100], int ArrayLength, int From, int To)
	{

		for (int i = 0; i < ArrayLength; i++)
		{
			Arr[i] = RandomNumber(From, To);
		}
	}

	static void FillArrayWithRandomWords(std::string arr[100], int arrLength, enCharType CharType, short Length)
	{
		for (int i = 0; i < arrLength; i++)
		{
			arr[i] = GenerateWord(CharType, Length);
		}
	}

	static void FillArrayWithRandomKeys(std::string arr[100], int arrLength, enCharType CharType)
	{
		for (int i = 0; i < arrLength; i++)
		{
			arr[i] = GenerateKey(CharType);
		}
	}

	static int HowManyTimesNumberIsRepeatedInArray(int Number, int Arr[100], int ArrLength)
	{
		int Count = 0;

		for (int i = 0; i < ArrLength; i++)
		{
			if (Arr[i] == Number)
				Count++;
		}

		return Count;
	}

	static int MaxNumberInArray(int Arr[100], int ArrLength)
	{
		int MaxNumber = 0;

		for (int i = 0; i < ArrLength; i++)
		{
			if (Arr[i] > MaxNumber)
				MaxNumber = Arr[i];
		}

		return MaxNumber;
	}

	static int MinNumberInArray(int Arr[100], int ArrLength)
	{
		int MinNumber = 0;
		MinNumber = Arr[0];

		for (int i = 0; i < ArrLength; i++)
		{
			if (Arr[i] < MinNumber)
				MinNumber = Arr[i];
		}

		return MinNumber;
	}

	static int SumArray(int Arr[100], int ArrLength)
	{
		int Sum = 0;

		for (int i = 0; i < ArrLength; i++)
		{
			Sum += Arr[i];
		}

		return Sum;
	}

	static float ArrayAverage(int Arr[100], int ArrLength)
	{
		return (float)SumArray(Arr, ArrLength) / ArrLength;
	}

	static void CopyArray(int ArrSource[100], int ArrDestination[100], int ArrLength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			ArrDestination[i] = ArrSource[i];
		}
	}

	static short FindNumberPositionInArray(int arr[100], int arrLength, int NumberToFind)
	{
		for (int i = 0; i < arrLength; i++)
		{
			if (arr[i] == NumberToFind)
				return i;
		}

		return -1;
	}

	static std::string Tabs(short NumberOfTabs)
	{
		std::string Word = "";

		for (int i = 0; i < NumberOfTabs; i++)
		{
			Word += '\t';
		}

		return Word;
	}

	static std::string EncryptText(std::string Text, short EncryptionKey = 5)
	{
		for (int i = 0; i < Text.length(); i++)
		{

			Text[i] = char((int)Text[i] + EncryptionKey);
		}

		return Text;
	}

	static std::string DecryptText(std::string Text, short EncryptionKey = 5)
	{
		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = char((int)Text[i] - EncryptionKey);
		}

		return Text;
	}

	static std::string NumberToText(int Number)
	{

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			std::string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
		"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
		  "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return  arr[Number] + " ";

		}

		if (Number >= 20 && Number <= 99)
		{
			std::string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return  arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return  "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return  "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return  "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return  "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}


	}

	static std::string ColorText(enColor Color, std::string Text)
	{
		switch (Color)
		{
		case RED:
			return  "\033[31m" + Text + "\033[0m";

		case GREEN:
			return "\033[32m" + Text + "\033[0m";

		case YELLOW:
			return "\033[33m" + Text + "\033[0m";

		case BLUE:
			return "\033[34m" + Text + "\033[0m";

		case MAGENTA:
			return "\033[35m" + Text + "\033[0m";

		case CYAN:
			return "\033[36m" + Text + "\033[0m";

		case LIGHTGREEN:
			return "\033[92m" + Text + "\033[0m";

		case WHITE:
			return "\033[0m" + Text + "\033[0m";

		}

	}

	static void DrawLine(char Symbol = '-', short LineLength = 118, short LeadingSpaces = 0)
	{
		std::cout << std::left << std::setw(LeadingSpaces) << "" << ColorText(clsUtil::BLUE, "+");
		std::cout << ColorText(clsUtil::LIGHTGREEN, std::string(LineLength, Symbol));
		std::cout << ColorText(clsUtil::BLUE, "+") << std::endl;
	}

	static void DrawLine(clsUtil::enColor Color, char Symbol = '-', short LineLength = 118, short LeadingSpaces = 0)
	{
		std::cout << std::left << std::setw(LeadingSpaces) << "" << ColorText(Color, "+");
		std::cout << ColorText(Color, std::string(LineLength, Symbol));
		std::cout << ColorText(Color, "+") << std::endl;
	}

	static void DrawCardLine()
	{
		std::cout << ColorText(clsUtil::BLUE, "|");
		std::cout << ColorText(clsUtil::LIGHTGREEN, std::string(30, '-'));
		std::cout << ColorText(clsUtil::BLUE, "|");
	}

	static void PrintTitle(std::string Title, clsUtil::enColor Color, short Length = 120, short LeadingSpaces = 0)
	{
		// I did this because when the lenght of the title is odd I need an extra space befor closing the title box
		// And when length is even I don't need the extra space.
		short SpacesBeforClosingTheTitleBox = 2;

		if ((Title.size() % 2) != 0)
			SpacesBeforClosingTheTitleBox = 1;

		short TitleSpeacing = (Length - Title.size()) / 2;

		std::cout << std::left << std::setw(LeadingSpaces) << "" << ColorText(Color, "|") << std::string(TitleSpeacing, ' ') << Title;
		std::cout << std::string(TitleSpeacing - SpacesBeforClosingTheTitleBox, ' ') << ColorText(Color, "|") << "\n";
	}

	static void PrintTitle(std::string Title, short Length = 120, short LeadingSpaces = 0)
	{
		// I did this because when the lenght of the title is odd I need an extra space befor closing the title box
		// And when length is even I don't need the extra space.
		short SpacesBeforClosingTheTitleBox = 2;

		if ((Title.size() % 2) != 0)
			SpacesBeforClosingTheTitleBox = 1;

		short TitleSpeacing = (Length - Title.size()) / 2;

		std::cout << std::left << std::setw(LeadingSpaces) << "" << ColorText(clsUtil::LIGHTGREEN, "|") << std::string(TitleSpeacing, ' ') << Title;
		std::cout << std::string(TitleSpeacing - SpacesBeforClosingTheTitleBox, ' ') << ColorText(clsUtil::LIGHTGREEN, "|") << "\n";
	}

	static std::string ColorTextBlock(enColor Color, enColor Color2, std::string Begain, std::string Text, std::string End)
	{
		return ColorText(Color, Begain) + ColorText(Color2, Text) + ColorText(Color, End);
	}

	static void PrintTableBoxTitle(std::string BoxTitle, short BoxSize, bool IsLastBox = false)
	{
		//std::cout << std::setw(LeadingSpaces) << std::left << "";
		std::cout << ColorText(LIGHTGREEN, "| ") << std::left << std::setw(BoxSize) << BoxTitle;

		if(IsLastBox)
			std::cout << std::left << std::setw(1) << ColorText(LIGHTGREEN, "|") << std::endl;
	}

	static void PrintTableBoxContent(std::string Content, short BoxSize, bool IsLastBox = false)
	{
		std::cout << ColorText(LIGHTGREEN, "| ") << std::left << std::setw(BoxSize) << Content;
		
		if (IsLastBox)
			std::cout << std::left << std::setw(1) << ColorText(LIGHTGREEN, "|") << std::endl;
	}

	static void PrintMenuOption(std::string Option, short OptionOrder)
	{
		std::cout << ColorTextBlock(BLUE, LIGHTGREEN, "[", std::to_string(OptionOrder), "]") << " - " << Option <<".\n";
	}
};

