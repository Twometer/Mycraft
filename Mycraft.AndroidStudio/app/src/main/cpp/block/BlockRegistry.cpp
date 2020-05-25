//
// Created by twome on 17/06/2018.
//

#include <cstdlib>
#include "BlockRegistry.h"

Block **BlockRegistry::registry;

void BlockRegistry::initialize() {
    registry = new Block *[255];
    for (int i = 0; i < 255; i++) *(registry + i) = NULL;
    registerBlock(0, TEXTURE(23, 10)); // Missing texture block
    registerBlock(1, TEXTURE(2, 10)); // Stone
    registerBlock(2, TEXTURE(8, 5), TEXTURE(5, 5), TEXTURE(30, 1)); // Grass
    registerBlock(3, TEXTURE(30, 1)); // Dirt
    registerBlock(4, TEXTURE(3, 1)); // Cobblestone
    registerBlock(5, TEXTURE(29, 7)); // Wooden Planks
    registerBlock(6, TEXTURE(25, 9), Plant); // Sapling
    registerBlock(7, TEXTURE(5, 0)); // Bedrock
    registerBlock(8, TEXTURE(2, 12), Fluid); // Flowing water
    registerBlock(9, TEXTURE(3, 13), Fluid); // Still water
    registerBlock(10, TEXTURE(0, 13), Fluid); // Flowing Lava
    registerBlock(11, TEXTURE(0, 13), Fluid); // Still lava
    registerBlock(12, TEXTURE(16, 9)); // Sand
    registerBlock(13, TEXTURE(9, 5)); // Gravel
    registerBlock(14, TEXTURE(4, 5)); // Gold Ore
    registerBlock(15, TEXTURE(4, 6)); // Iron Ore
    registerBlock(16, TEXTURE(1, 1)); // Coal Ore
    registerBlock(17, TEXTURE(29, 6), TEXTURE(28, 6), TEXTURE(29, 6)); // Log
    registerBlock(18, TEXTURE(13, 6), Transparent); // Leaves
    registerBlock(19, TEXTURE(0, 10)); // Sponge
    registerBlock(20, TEXTURE(0, 4), Transparent); // Glass
    registerBlock(21, TEXTURE(11, 6)); // Lapis Lazuli Ore
    registerBlock(22, TEXTURE(10, 6)); // Lapis Lazuli Block
    registerBlock(23, TEXTURE(20, 7), TEXTURE(1, 2), TEXTURE(2, 10)); // Dispenser
    registerBlock(24, TEXTURE(21, 9), TEXTURE(19, 9), TEXTURE(17, 9)); // Sandstone
    registerBlock(25, TEXTURE(8, 6), TEXTURE(7, 6), TEXTURE(7, 6)); // Sandstone
    registerBlock(30, TEXTURE(27, 10), Plant); // Cobweb
    registerBlock(31, TEXTURE(15, 10), Plant); // Tall grass
    registerBlock(32, TEXTURE(17, 1), Plant); // Dead bush
    registerBlock(33, TEXTURE(23, 7), TEXTURE(22, 7), TEXTURE(20, 7)); // Piston
    registerBlock(35, TEXTURE(18, 11)); // Wool
    registerBlock(37, TEXTURE(18, 3), Plant); // Dandelion
    registerBlock(38, TEXTURE(23, 3), Plant); // Poppy
    registerBlock(39, TEXTURE(9, 7), Plant); // Brown Mushroom
    registerBlock(40, TEXTURE(10, 7), Plant); // Red Mushroom
    registerBlock(41, TEXTURE(3, 5)); // Gold Block
    registerBlock(42, TEXTURE(3, 6)); // Iron Block
    registerBlock(45, TEXTURE(15, 0)); // Bricks
    registerBlock(46, TEXTURE(18, 10), TEXTURE(17, 10), TEXTURE(16, 10)); // TNT
    registerBlock(47, TEXTURE(29, 7), TEXTURE(12, 0), TEXTURE(29, 7)); // Bookshelf
    registerBlock(48, TEXTURE(4, 1)); // Mossy Stone
    registerBlock(49, TEXTURE(19, 7)); // Obsidian
    registerBlock(50, TEXTURE(19, 10)); // Torch
    registerBlock(51, TEXTURE(15, 3), Plant); // Fire
    registerBlock(52, TEXTURE(4, 7)); // Spawner
    registerBlock(56, TEXTURE(29, 1)); // Diamond Ore
    registerBlock(57, TEXTURE(28, 1)); // Diamond Block
    registerBlock(58, TEXTURE(13, 1), TEXTURE(11, 1), TEXTURE(29, 7)); // Crafting Table
    registerBlock(59, TEXTURE(3, 11), Plant); // Wheat
    registerBlock(60, TEXTURE(11, 3), TEXTURE(30, 1), TEXTURE(30, 1)); // Farmland
    registerBlock(73, TEXTURE(4, 9)); // Redstone Ore
    registerBlock(74, TEXTURE(4, 9)); // Glowing Redstone Ore
    registerBlock(78, TEXTURE(30, 9), Transparent); // Snow
    registerBlock(79, TEXTURE(0, 6), Fluid); // Ice
    registerBlock(80, TEXTURE(30, 9)); // Snow
    registerBlock(89, TEXTURE(2, 5)); // Glowstone
    registerBlock(97, TEXTURE(2, 10)); // Stone Monster egg
    registerBlock(98, TEXTURE(3, 10)); // Stone Bricks
    registerBlock(103, TEXTURE(3, 7), TEXTURE(0, 7), TEXTURE(3, 7)); // Melon
    registerBlock(110, TEXTURE(12, 7), TEXTURE(11, 7), TEXTURE(30, 1)); // Mycelium
    registerBlock(111, TEXTURE(25, 10), Transparent); // Lily pad
    registerBlock(112, TEXTURE(14, 7)); // Nether bricks
    registerBlock(115, TEXTURE(17, 7), Plant); // Nether wart
    registerBlock(121, TEXTURE(10, 3)); // Endstone
    registerBlock(123, TEXTURE(2, 9)); // Redstone Lamp (off)
    registerBlock(124, TEXTURE(3, 9)); // Redstone Lamp (on)
    registerBlock(129, TEXTURE(3, 3)); // Emerald Ore
    registerBlock(133, TEXTURE(2, 3)); // Emerald Block
    registerBlock(137, TEXTURE(8, 1)); // Command Block
    registerBlock(141, TEXTURE(26, 0)); // Carrots
    registerBlock(142, TEXTURE(3, 8)); // Potatoes
    registerBlock(152, TEXTURE(29, 8)); // Redstone block
    registerBlock(153, TEXTURE(20, 8)); // Quartz Ore
    registerBlock(155, TEXTURE(19, 8)); // Quartz Block
    registerBlock(159, TEXTURE(25, 5)); // Hardened Clay
    registerBlock(161, TEXTURE(18, 6), Transparent); // Leaves 2
    registerBlock(162, TEXTURE(21, 6), TEXTURE(20, 6), TEXTURE(21, 6),
                  Transparent); // Acacia leaves
    registerBlock(165, TEXTURE(29, 9), Transparent); // Slime block
    registerBlock(166, TEXTURE(20, 11), Transparent); // Barrier
    registerBlock(168, TEXTURE(6, 8)); // Prismarine
    registerBlock(169, TEXTURE(28, 9)); // Prismarine Lantern
    registerBlock(170, TEXTURE(28, 5), TEXTURE(27, 5), TEXTURE(28, 5)); // Hay bale
    registerBlock(172, TEXTURE(10, 5)); // Hay bale
}

bool BlockRegistry::isTransparent(uint8_t id) {
    if (id == 0) return false;
    Block *block = *(registry + id);
    if (block == NULL) return false;
    return block->rendererType == Transparent || block->rendererType == Plant;
}

bool BlockRegistry::isFluid(uint8_t id) {
    if (id == 0) return false;
    Block *block = *(registry + id);
    if (block == NULL) return false;
    return block->rendererType == Fluid;
}

bool BlockRegistry::isPlant(uint8_t id) {
    if (id == 0) return false;
    Block *block = *(registry + id);
    if (block == NULL) return false;
    return block->rendererType == Plant;
}

Block *BlockRegistry::getBlock(uint8_t id) {
    if (id == 0) return registry[0];
    Block *block = *(registry + id);
    if (block == NULL) return registry[0];
    return block;
}

void
BlockRegistry::registerBlock(uint8_t id, TEXTURE topTex, TEXTURE sideTex, TEXTURE bottomTex,
                             RendererType type) {
    registry[id] = new Block(id, topTex, sideTex, bottomTex, type);
}

void BlockRegistry::registerBlock(uint8_t id, TEXTURE tex, RendererType type) {
    registry[id] = new Block(id, tex, tex, tex, type);
}

void
BlockRegistry::registerBlock(uint8_t id, TEXTURE topTex, TEXTURE sideTex, TEXTURE bottomTex) {
    registry[id] = new Block(id, topTex, sideTex, bottomTex, RendererType::Solid);
}

void BlockRegistry::registerBlock(uint8_t id, TEXTURE tex) {
    registry[id] = new Block(id, tex, tex, tex, RendererType::Solid);
}