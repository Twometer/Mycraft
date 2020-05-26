//
// Created by twome on 17/06/2018.
//

#include <cstdlib>
#include "BlockRegistry.h"

Block **BlockRegistry::registry;

void BlockRegistry::initialize() {
    registry = new Block *[255];
    for (int i = 0; i < 255; i++)
        registry[i] = nullptr;

    registerBlock(0, Sprite(23, 10), Solid, true); // Missing texture block or air
    registerBlock(1, Sprite(2, 10)); // Stone
    registerBlock(2, Sprite(8, 5), Sprite(5, 5), Sprite(30, 1)); // Grass
    registerBlock(3, Sprite(30, 1)); // Dirt
    registerBlock(4, Sprite(3, 1)); // Cobblestone
    registerBlock(5, Sprite(29, 7)); // Wooden Planks
    registerBlock(6, Sprite(25, 9), Plant, true); // Sapling
    registerBlock(7, Sprite(5, 0)); // Bedrock
    registerBlock(8, Sprite(2, 12), Fluid, true); // Flowing water
    registerBlock(9, Sprite(3, 13), Fluid, true); // Still water
    registerBlock(10, Sprite(0, 13), Fluid, true); // Flowing Lava
    registerBlock(11, Sprite(0, 13), Fluid, true); // Still lava
    registerBlock(12, Sprite(16, 9)); // Sand
    registerBlock(13, Sprite(9, 5)); // Gravel
    registerBlock(14, Sprite(4, 5)); // Gold Ore
    registerBlock(15, Sprite(4, 6)); // Iron Ore
    registerBlock(16, Sprite(1, 1)); // Coal Ore
    registerBlock(17, Sprite(29, 6), Sprite(28, 6), Sprite(29, 6)); // Log
    registerBlock(18, Sprite(13, 6), Transparent); // Leaves
    registerBlock(19, Sprite(0, 10)); // Sponge
    registerBlock(20, Sprite(0, 4), Transparent); // Glass
    registerBlock(21, Sprite(11, 6)); // Lapis Lazuli Ore
    registerBlock(22, Sprite(10, 6)); // Lapis Lazuli Block
    registerBlock(23, Sprite(20, 7), Sprite(1, 2), Sprite(2, 10)); // Dispenser
    registerBlock(24, Sprite(21, 9), Sprite(19, 9), Sprite(17, 9)); // Sandstone
    registerBlock(25, Sprite(8, 6), Sprite(7, 6), Sprite(7, 6)); // Sandstone
    registerBlock(30, Sprite(27, 10), Plant, true); // Cobweb
    registerBlock(31, Sprite(15, 10), Plant, true); // Tall grass
    registerBlock(32, Sprite(17, 1), Plant, true); // Dead bush
    registerBlock(33, Sprite(23, 7), Sprite(22, 7), Sprite(20, 7)); // Piston
    registerBlock(35, Sprite(18, 11)); // Wool
    registerBlock(37, Sprite(18, 3), Plant, true); // Dandelion
    registerBlock(38, Sprite(23, 3), Plant, true); // Poppy
    registerBlock(39, Sprite(9, 7), Plant, true); // Brown Mushroom
    registerBlock(40, Sprite(10, 7), Plant, true); // Red Mushroom
    registerBlock(41, Sprite(3, 5)); // Gold Block
    registerBlock(42, Sprite(3, 6)); // Iron Block
    registerBlock(45, Sprite(15, 0)); // Bricks
    registerBlock(46, Sprite(18, 10), Sprite(17, 10), Sprite(16, 10)); // TNT
    registerBlock(47, Sprite(29, 7), Sprite(12, 0), Sprite(29, 7)); // Bookshelf
    registerBlock(48, Sprite(4, 1)); // Mossy Stone
    registerBlock(49, Sprite(19, 7)); // Obsidian
    registerBlock(50, Sprite(19, 10), Plant, true); // Torch
    registerBlock(51, Sprite(15, 3), Plant, true); // Fire
    registerBlock(52, Sprite(4, 7)); // Spawner
    registerBlock(56, Sprite(29, 1)); // Diamond Ore
    registerBlock(57, Sprite(28, 1)); // Diamond Block
    registerBlock(58, Sprite(13, 1), Sprite(11, 1), Sprite(29, 7)); // Crafting Table
    registerBlock(59, Sprite(3, 11), Plant, true); // Wheat
    registerBlock(60, Sprite(11, 3), Sprite(30, 1), Sprite(30, 1)); // Farmland
    registerBlock(73, Sprite(4, 9)); // Redstone Ore
    registerBlock(74, Sprite(4, 9)); // Glowing Redstone Ore
    registerBlock(78, Sprite(30, 9), Transparent); // Snow
    registerBlock(79, Sprite(0, 6), Fluid); // Ice
    registerBlock(80, Sprite(30, 9)); // Snow
    registerBlock(89, Sprite(2, 5)); // Glowstone
    registerBlock(97, Sprite(2, 10)); // Stone Monster egg
    registerBlock(98, Sprite(3, 10)); // Stone Bricks
    registerBlock(103, Sprite(3, 7), Sprite(0, 7), Sprite(3, 7)); // Melon
    registerBlock(110, Sprite(12, 7), Sprite(11, 7), Sprite(30, 1)); // Mycelium
    registerBlock(111, Sprite(25, 10), Transparent); // Lily pad
    registerBlock(112, Sprite(14, 7)); // Nether bricks
    registerBlock(115, Sprite(17, 7), Plant, true); // Nether wart
    registerBlock(121, Sprite(10, 3)); // Endstone
    registerBlock(123, Sprite(2, 9)); // Redstone Lamp (off)
    registerBlock(124, Sprite(3, 9)); // Redstone Lamp (on)
    registerBlock(129, Sprite(3, 3)); // Emerald Ore
    registerBlock(133, Sprite(2, 3)); // Emerald Block
    registerBlock(137, Sprite(8, 1)); // Command Block
    registerBlock(141, Sprite(26, 0)); // Carrots
    registerBlock(142, Sprite(3, 8)); // Potatoes
    registerBlock(152, Sprite(29, 8)); // Redstone block
    registerBlock(153, Sprite(20, 8)); // Quartz Ore
    registerBlock(155, Sprite(19, 8)); // Quartz Block
    registerBlock(159, Sprite(25, 5)); // Hardened Clay
    registerBlock(161, Sprite(18, 6), Transparent); // Leaves 2
    registerBlock(162, Sprite(21, 6), Sprite(20, 6), Sprite(21, 6), Transparent); // Acacia leaves
    registerBlock(165, Sprite(29, 9), Transparent); // Slime block
    registerBlock(166, Sprite(20, 11), Transparent); // Barrier
    registerBlock(168, Sprite(6, 8)); // Prismarine
    registerBlock(169, Sprite(28, 9)); // Prismarine Lantern
    registerBlock(170, Sprite(28, 5), Sprite(27, 5), Sprite(28, 5)); // Hay bale
    registerBlock(172, Sprite(10, 5)); // Hay bale
}

bool BlockRegistry::isTransparent(uint8_t id) {
    Block *block = getBlock(id);
    return block != nullptr && (block->rendererType == Transparent || block->rendererType == Plant);
}

Block *BlockRegistry::getBlock(uint8_t id) {
    if (id < 0 || id > 255) return nullptr;
    Block *block = registry[id];
    return block == nullptr ? registry[0] : block;
}

void BlockRegistry::registerBlock(uint8_t id, Sprite topTex, Sprite sideTex, Sprite bottomTex,
                                  RendererType type, bool noClip) {
    registry[id] = new Block(id, topTex, sideTex, bottomTex, type, noClip);
}

void BlockRegistry::registerBlock(uint8_t id, Sprite allTex, RendererType type, bool noClip) {
    registry[id] = new Block(id, allTex, allTex, allTex, type, noClip);
}