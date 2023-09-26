#pragma once

#include <ZC/ZC_Noncopyable.h>

class ZC_Buffer : public ZC_Noncopyable
{
public:
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

protected:
    unsigned id = 0;

	ZC_Buffer();
};