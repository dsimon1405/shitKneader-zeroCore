#pragma once

#include <ZC/ZC_Noncopyable.h>

class ZC_VAO : public ZC_Noncopyable
{
public:
	ZC_VAO();
	~ZC_VAO();
	void Bind() const;
	void Unbind() const;

private:
	unsigned id;
};