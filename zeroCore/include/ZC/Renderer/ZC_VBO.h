#pragma once

#include <ZC/Renderer/ZC_Buffer.h>

class ZC_VBO : public ZC_Buffer
{
public:
    ZC_VBO() = default;
	~ZC_VBO();
	virtual void Bind() const override;
	virtual void Unbind() const override;
};