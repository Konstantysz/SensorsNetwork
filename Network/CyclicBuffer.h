#pragma once
#include <queue>
#include <string>

namespace NetworkSystem
{
	class CyclicBuffer
	{
	public:
		CyclicBuffer(size_t size);

		void Push(const std::string& value);

		void Pop();

	private:
		std::queue<std::string> container;
		size_t size;
	};
}

