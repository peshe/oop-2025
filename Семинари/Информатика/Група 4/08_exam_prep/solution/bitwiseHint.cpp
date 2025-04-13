// Just a hint on how to make the date class using bitwise operations

const uint32_t DAY_BITS = 5;
const uint32_t MONTH_BITS = 4;
const uint32_t YEAR_BITS = 6;
const uint32_t YEAR_OFFSET = DAY_BITS + MONTH_BITS;
const uint32_t MONTH_OFFSET = DAY_BITS;

uint16_t time; // We store the data in this field in the class

unsigned Date::GetMonth() const {
    return ((time >> MONTH_OFFSET) & ((1 << MONTH_BITS) - 1));
}

void Date::SetMonth(unsigned month) {
    uint32_t clearMask = ~(((1 << MONTH_BITS) - 1) << MONTH_OFFSET);
    time = time & clearMask;

    uint32_t shiftedMonth = month << MONTH_OFFSET;

    time = time | shiftedMonth;
}
