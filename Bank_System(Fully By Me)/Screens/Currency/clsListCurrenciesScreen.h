#pragma once

#include "../clsScreen.h"
#include "../../Core/clsCurrency.h"

class clsListCurrenciesScreen : protected clsScreen
{
private:

	static void _PrintCurrencyRecordLine(clsCurrency& Currency)
	{
		//std::cout << std::setw(2) << std::left << "";
		clsUtil::PrintTableBoxContent(Currency.Country(), 40);
		clsUtil::PrintTableBoxContent(Currency.CurrencyCode(), 10);
		clsUtil::PrintTableBoxContent(Currency.CurrencyName(), 40);
		clsUtil::PrintTableBoxContent(std::to_string(Currency.Rate()), 21, true);
	}

public:

	static void ShowListClientScreen()
	{
		std::vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		std::string Title = "Currencies List Screen";
		std::string SubTitle = "(" + std::to_string(vCurrencies.size()) + ") Currencies";

		_DrawScreenHeader(Title, SubTitle);

		
		clsUtil::DrawLine('-', 118);
		clsUtil::PrintTableBoxTitle("Country", 40);
		clsUtil::PrintTableBoxTitle("Code", 10);
		clsUtil::PrintTableBoxTitle("Name", 40);
		clsUtil::PrintTableBoxTitle("Rate/(1$)", 21, true);
		clsUtil::DrawLine('-', 118);
		
		for (clsCurrency& Currency : vCurrencies)
			_PrintCurrencyRecordLine(Currency);
		
		clsUtil::DrawLine('-', 118);
	}
};

