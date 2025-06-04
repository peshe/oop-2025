#pragma once

class IPrintable {
public:
	virtual ~IPrintable() = default;

	virtual void print() const = 0;
};

