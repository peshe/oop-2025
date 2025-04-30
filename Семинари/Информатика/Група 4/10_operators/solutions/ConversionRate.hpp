#pragma once

#include "Currency.hpp"


struct ConversionRate {
    double conversionRate;
    Currency oldCurrency;
    Currency newCurrency;
};
