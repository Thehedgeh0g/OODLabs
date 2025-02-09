#pragma once
#include <array>
#include <cassert>

class Tile {
public:
	constexpr static int SIZE = 8;

	Tile(uint32_t color = ' ') noexcept {
		pixels.fill(color);

		assert(m_instanceCount >= 0);
		++m_instanceCount;
	}

	Tile(const Tile& other) : pixels(other.pixels) {
		assert(m_instanceCount >= 0);
		++m_instanceCount;
	}

	~Tile() {
		--m_instanceCount;
		assert(m_instanceCount >= 0);
	}

	void SetPixel(Point p, uint32_t color) noexcept {
		if (IsPointInSize(p, { SIZE, SIZE })) {
			pixels[p.y * SIZE + p.x] = color;
		}
	}

	char GetPixel(Point p) const noexcept {
		if (IsPointInSize(p, { SIZE, SIZE })) {
			return pixels[p.y * SIZE + p.x];
		}
		return ' ';
	}

	static int GetInstanceCount() noexcept {
		return m_instanceCount;
	}

private:
	static inline int m_instanceCount = 0;
	std::array<uint32_t, SIZE * SIZE> pixels;
};
