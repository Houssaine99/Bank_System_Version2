#pragma once

#include "Core/clsUser.h"
#include "Core/clsReceipt.h"

clsUser CurrentUser = clsUser::Find("");

std::string clsReceipt::ReceiptFilePath = "Data/ReceiptHistory.txt";
