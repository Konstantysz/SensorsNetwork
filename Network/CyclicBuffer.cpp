#include "pch.h"
#include "CyclicBuffer.h"

namespace NetworkSystem
{
	CyclicBuffer::CyclicBuffer(size_t size) : container(std::queue<std::string>()), size(size)
	{
	}
	
	void CyclicBuffer::Push(const std::string& value)
	{
		if (container.size() == size) 
		{
			container.pop();
		}
		container.push(value);
	}

	void CyclicBuffer::Pop()
	{
		container.pop();
	}
}
