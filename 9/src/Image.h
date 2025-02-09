#pragma once
#include <vector>
#include <stdexcept>

#include "CoW.h"
#include "Geom.h"
#include "Tile.h"

class Image {
public:
	explicit Image(Size size, uint32_t color = ' ') {
		if (size.width <= 0 || size.height <= 0) {
			throw std::out_of_range("Invalid image size");
		}
		img_size = size;

		int horizontal_tiles = (size.width + Tile::SIZE - 1) / Tile::SIZE;
		int vertical_tiles = (size.height + Tile::SIZE - 1) / Tile::SIZE;

		tiles.resize(vertical_tiles, std::vector<CoW<Tile>>(horizontal_tiles, Tile(color)));
	}

	[[nodiscard]] Size GetSize() const noexcept {
		return img_size;
	}

	[[nodiscard]] uint32_t GetPixel(Point p) const noexcept {
		if (!IsPointInSize(p, img_size)) {
			return ' ';
		}
		auto [tile_x, tile_y, local_p] = GetTileCoordinates(p);
		return tiles[tile_y][tile_x]->GetPixel(local_p);
	}

	void SetPixel(Point p, uint32_t color) {
		if (!IsPointInSize(p, img_size)) {
			return;
		}
		auto [tile_x, tile_y, local_p] = GetTileCoordinates(p);
		tiles[tile_y][tile_x].Write()->SetPixel(local_p, color);
	}

private:
	Size img_size;
	std::vector<std::vector<CoW<Tile>>> tiles;

	struct TileCoords {
		int tile_x = 0;
		int tile_y = 0;
		Point local_p{};
	};

	[[nodiscard]] static TileCoords GetTileCoordinates(Point p) noexcept {
		int tile_x = p.x / Tile::SIZE;
		int tile_y = p.y / Tile::SIZE;
		Point local_p{ p.x % Tile::SIZE, p.y % Tile::SIZE };
		return { tile_x, tile_y, local_p };
	}
};
