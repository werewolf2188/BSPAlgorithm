//
//  MapSprite.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 3/25/21.
//

#include "MapSprite.h"
#include "Constants.h"
#include "Math.h"
#include <iostream>
#include <queue>

struct Item {
    unsigned int sectorno;
    int sx1;
    int sx2;
};

bool operator==(Item i1, Item i2) {
    return i1.sectorno == i2.sectorno &&
    i1.sx1 == i2.sx1 &&
    i1.sx2 == i2.sx2;
}

bool operator!=(Item i1, Item i2) {
    return !(i1 == i2);
}

MapSprite::MapSprite(MapLoader &loader): loader(loader),
player(loader.getPlayerInitialLocation()) {
    move_player(0,0);
}

/*
 For now I will replicate the algorithm and then, once I get the grasp of it,
 I will refactor it.
 */
void MapSprite::onRender(Graphics *g) {
    const Size windowSize = g->getDrawableSize();
    const int max_queues = 32;

//    std::queue<Item> queue;
    Item queue[max_queues];
    Item *head = queue; // They are referencing the same spot
    Item *tail = queue; // That means when I assign head, I also assign tail.

    //
    int ytop[windowSize.width];
    int ybottom[windowSize.width];
    int renderedsectors[loader.getSectors().size()];
    
    //
    for(int x = 0; x < windowSize.width; ++x) ytop[x] = 0;
    for(int x = 0; x < windowSize.width; ++x) ybottom[x] = windowSize.height - 1;
    for(int n = 0; n < loader.getSectors().size(); ++n) renderedsectors[n] = 0;

    //
//    queue.push({ loader.getPlayerInitialLocation().getSector(), 0, windowSize.width - 1});
    *head = { player.getSector(), 0, windowSize.width - 1 };
    // ++head is moving the pointer before checking if it is in the end of the queue
    if(++head == queue + max_queues) { // TODO: This is making a circular queue to reset to position 0
        head = queue;
    }
    
    do {
        const Item now = *tail;
        // ++tail is moving the pointer before checking if it is in the end of the queue
        if(++tail == queue + max_queues) { // TODO: This is making a circular queue to reset to position 0
            tail = queue;
        }
        // 0x21 = 33
        // 0x20 = 32
        if(renderedsectors[now.sectorno] & 0x21) {
            continue; // Odd = still rendering, 0x20 = give up
        }
        ++renderedsectors[now.sectorno];

        Sector *sector = loader.getSectors()[now.sectorno];
        for (int s = 0; s < sector->getNPoints(); s++) {
            // Preparing drawing
            // TODO: There are many floats that can become Vector2 in the future
            /* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
            float vx1 = sector->getVertices()[s + 0]->x - player.getPosition().x;
            float vy1 = sector->getVertices()[s + 0]->y - player.getPosition().y;
            float vx2 = sector->getVertices()[s + 1]->x - player.getPosition().x;
            float vy2 = sector->getVertices()[s + 1]->y - player.getPosition().y;
            /* Rotate them around the player's view */
            float pcos = player.getAnglecos();
            float psin = player.getAnglesin();
            float tx1 = vx1 * psin - vy1 * pcos;
            float tz1 = vx1 * pcos + vy1 * psin;
            float tx2 = vx2 * psin - vy2 * pcos;
            float tz2 = vx2 * pcos + vy2 * psin;
            /* Is the wall at least partially in front of the player? */
            if(tz1 <= 0 && tz2 <= 0) continue;
            /* If it's partially behind the player, clip it against player's view frustrum */
            if(tz1 <= 0 || tz2 <= 0) {
                float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
                // Find an intersection between the wall and the approximate edges of player's view
                Vector2 i1 = intersect({ tx1, tz1 }, { tx2, tz2 }, { -nearside, nearz }, { -farside, farz });
                Vector2 i2 = intersect({ tx1, tz1 }, { tx2, tz2 }, { nearside, nearz }, { farside, farz });
                if(tz1 < nearz) {
                    if(i1.y > 0) {
                        tx1 = i1.x;
                        tz1 = i1.y;
                    } else {
                        tx1 = i2.x;
                        tz1 = i2.y;
                    }
                }
                if(tz2 < nearz) {
                    if(i1.y > 0) {
                        tx2 = i1.x;
                        tz2 = i1.y;
                    } else {
                        tx2 = i2.x;
                        tz2 = i2.y;
                    }
                }
            }
            /* Do perspective transformation */
            float xscale1 = hfov(windowSize.height) / tz1;
            float yscale1 = vfov(windowSize.height) / tz1;
            int x1 = windowSize.width/2 - (int)(tx1 * xscale1);
            float xscale2 = hfov(windowSize.height) / tz2;
            float yscale2 = vfov(windowSize.height) / tz2;
            int x2 = windowSize.width/2 - (int)(tx2 * xscale2);
            if(x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) {
                continue; // Only render if it's visible
            }
            /* Acquire the floor and ceiling heights, relative to where the player's view is */
            float yceil  = sector->getCeil()  - player.getPosition().z;
            float yfloor = sector->getFloor() - player.getPosition().z;
            /* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
            int neighbor = sector->getNeighbors()[s];
            float nyceil=0, nyfloor=0;
            if(neighbor >= 0) // Is another sector showing through this portal?
            {
                nyceil  = loader.getSectors()[neighbor]->getCeil()  -
                player.getPosition().z;
                nyfloor = loader.getSectors()[neighbor]->getFloor() -
                player.getPosition().z;
            }
            /* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
            int y1a = windowSize.height / 2 - (int)(yaw(yceil, tz1) * yscale1);
            int y1b = windowSize.height / 2 - (int)(yaw(yfloor, tz1) * yscale1);
            int y2a = windowSize.height / 2 - (int)(yaw(yceil, tz2) * yscale2);
            int y2b = windowSize.height / 2 - (int)(yaw(yfloor, tz2) * yscale2);
            /* The same for the neighboring sector */
            int ny1a = windowSize.height / 2 - (int)(yaw(nyceil, tz1) * yscale1);
            int ny1b = windowSize.height / 2 - (int)(yaw(nyfloor, tz1) * yscale1);
            int ny2a = windowSize.height / 2 - (int)(yaw(nyceil, tz2) * yscale2);
            int ny2b = windowSize.height / 2 - (int)(yaw(nyfloor, tz2) * yscale2);
            /* Render the wall. */
            int beginx = std::max(x1, now.sx1);
            int endx = std::min(x2, now.sx2);
            for(int x = beginx; x <= endx; ++x) {
                /* Calculate the Z coordinate for this point. (Only used for lighting.) */
                int z = ((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
                /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
                int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a; // top
                int cya = clamp(ya, ytop[x], ybottom[x]); // top
                int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b; // bottom
                int cyb = clamp(yb, ytop[x], ybottom[x]); // bottom

                /* Render ceiling: everything above this sector's ceiling height. */
                Color top1 = makeFromRGB(0x111111);
                Color middle1 = makeFromRGB(0x222222);
                Color bottom1 = makeFromRGB(0x111111);
                draw_vertical_line(g, x, ytop[x], cya - 1, top1, middle1, bottom1, windowSize);
                /* Render floor: everything below this sector's floor height. */
                Color top2 = makeFromRGB(0x0000FF);
                Color middle2 = makeFromRGB(0x0000AA);
                Color bottom2 = makeFromRGB(0x0000FF);
                draw_vertical_line(g, x, cyb + 1, ybottom[x], top2, middle2, bottom2, windowSize);

                /* Is there another sector behind this edge? */
                if(neighbor >= 0) {
                    /* Same for _their_ floor and ceiling */
                    int nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a;
                    int cnya = clamp(nya, ytop[x],ybottom[x]);
                    int nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b;
                    int cnyb = clamp(nyb, ytop[x],ybottom[x]);

                    /* If our ceiling is higher than their ceiling, render upper wall */
                    Color r1 = makeFromRGB(0x010101 * (255 - z)); // Color
                    Color r2 = makeFromRGB(0x040007 * (31 - z / 8)); // Color
                    draw_vertical_line(g, x, cya, cnya - 1, BLACK, x == x1 || x == x2 ? BLACK : r1, BLACK, windowSize);
                    // Between our and their ceiling
                    ytop[x] = clamp(std::max(cya, cnya), ytop[x], windowSize.height - 1);   // Shrink the remaining window below these ceilings
                    /* If our floor is lower than their floor, render bottom wall */
                    // Between their and our floor
                    draw_vertical_line(g, x, cnyb + 1, cyb, BLACK, x == x1 || x == x2 ? BLACK : r2, BLACK, windowSize);
                    ybottom[x] = clamp(std::min(cyb, cnyb), 0, ybottom[x]); //
                } else {
                    /* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
                    Color r = makeFromRGB(0x010101 * (255 - z)); // Color
                    draw_vertical_line(g, x, cya, cyb, BLACK, x == x1 || x == x2 ? BLACK : r, BLACK, windowSize);
                }
            }
            /* Schedule the neighboring sector for rendering within the window formed by this wall. */
            int queue_position = (head + max_queues + 1 - tail) % max_queues; // This checks the position of the circular queue
            if(neighbor >= 0 && endx >= beginx && queue_position) {
                *head = { static_cast<unsigned int>(neighbor), beginx, endx };
                // ++head is moving the pointer before checking if it is in the end of the queue
                if(++head == queue + max_queues) { // TODO: This is making a circular queue to reset to position 0
                    head = queue;
                }
            }
        }
    // for s in sector's edges
    ++renderedsectors[now.sectorno];
    } while (head != tail);

//    std::cout << "Render" << std::endl;
}
bool MapSprite::onRelativeMouse(Point p) {
    player.setAngle(player.getAngle() + (p.x * 0.03f));
    yawVar = clamp(yawVar - (-p.y) * 0.05f, -5.0f, 5.0f);
    player.setYaw(yawVar - player.getVelocity().z * 0.5f);
    move_player(0,0);
    return true;
}

bool MapSprite::onKeyPress(const Key &key) {
    bool handle = false;
    bool pushing = false;
    Vector2 mov = { 0, 0 };
    if (key == SDL_SCANCODE_W) {
        mov.x += player.getAnglecos() * 0.2f;
        mov.y += player.getAnglesin() * 0.2f;
        pushing = true;
        handle = true;
    } else if (key == SDL_SCANCODE_S) {
        mov.x -= player.getAnglecos() * 0.2f;
        mov.y -= player.getAnglesin() * 0.2f;
        pushing = true;
        handle = true;
    }
    if (key == SDL_SCANCODE_A) {
        mov.x += player.getAnglesin() * 0.2f;
        mov.y -= player.getAnglecos() * 0.2f;
        pushing = true;
        handle = true;
    } else if (key == SDL_SCANCODE_D) {
        mov.x -= player.getAnglesin() * 0.2f;
        mov.y += player.getAnglecos() * 0.2f;
        pushing = true;
        handle = true;
    }
    if (key == SDL_SCANCODE_RCTRL ||
               key == SDL_SCANCODE_LCTRL) {
        ducking = true;
        falling = true;
        handle = true;
    }
    if (key == SDL_SCANCODE_SPACE) {
        if(ground) {
            Vector3 z = { 0, 0, 0.5f };
            player.setVelocity(player.getVelocity() + z);
            falling = true;
        }
    }
    float acceleration = pushing ? 0.4 : 0.2;

    player.setVelocity({ player.getVelocity().x * (1 - acceleration) + mov.x * acceleration,
                         player.getVelocity().y * (1 - acceleration) + mov.y * acceleration,
                        0.0f
    });
    if(pushing) {
        moving = 1;
    }
    /* Vertical collision detection */
    ground = !falling;
    if (falling) {
        handle_falling();
    }
    /* Horizontal collision detection */
    if(moving) {
        handle_moving();
    }
    return handle;
}

bool MapSprite::onKeyRelease(const Key &key) {
    bool handle = false;
    if (key == SDL_SCANCODE_RCTRL ||
        key == SDL_SCANCODE_LCTRL) {
        ducking = false;
        falling = true;
        handle = true;
    }
    /* Vertical collision detection */
    ground = !falling;
    if (falling) {
        handle_falling();
    }
    /* Horizontal collision detection */
    if(moving) {
        handle_moving();
    }
    return handle;
}

// MARK: Private
void MapSprite::handle_falling() {
    Vector3 gravity = { 0, 0, 0.05f };
    player.setVelocity(player.getVelocity() - gravity);
    float nextz = player.getPosition().z + player.getVelocity().z;
    if (player.getVelocity().z < 0 && nextz < loader.getSectors()[player.getSector()]->getFloor() + current_eye_height()) {
        Vector3 gro = { player.getPosition().x,
                        player.getPosition().y,
                        loader.getSectors()[player.getSector()]->getFloor() + current_eye_height() };
        player.setPosition(gro);
        Vector3 vel = { player.getVelocity().x, player.getVelocity().y, 0 };
        player.setVelocity(vel);
        falling = false;
        ground = true;
    } else if (player.getVelocity().z > 0 && nextz > loader.getSectors()[player.getSector()]->getCeil()) {
        Vector3 vel = { player.getVelocity().x, player.getVelocity().y, 0 };
        player.setVelocity(vel);
        falling = true;
    }
    if (falling) {
        Vector3 vel = { player.getPosition().x,
                        player.getPosition().y,
                        player.getPosition().z + (player.getVelocity().z / 0.05f) };
        player.setPosition(vel);
        moving = true;
    }
}

void MapSprite::handle_moving() {
    float px = player.getPosition().x;
    float py = player.getPosition().y;
    float dx = player.getVelocity().x;
    float dy = player.getVelocity().y;
    
    Sector* sector = loader.getSectors()[player.getSector()];
    auto vert = sector->getVertices();
    for (int s = 0; s < sector->getNPoints(); ++s) {
        Vector2 vPos = { px, py };
        Vector2 vPosDx = { px + dx, py + dy };
        Vector2 vVert0 = { vert[s + 0]->x, vert[s + 0]->y };
        Vector2 vVert1 = { vert[s + 1]->x, vert[s + 1]->y };
        bool intersect = intersectBox(vPos, vPosDx, vVert0, vVert1);
        float ps = pointSide(vPosDx, vVert0, vVert1);
        if (intersect && ps < 0) {
            /* Check where the hole is. */
            float hole_low  = sector->getNeighbors()[s] < 0 ?  9e9 : std::max(sector->getFloor(), loader.getSectors()[sector->getNeighbors()[s]]->getFloor());
            float hole_high = sector->getNeighbors()[s] < 0 ? -9e9 : std::min(sector->getCeil(),  loader.getSectors()[sector->getNeighbors()[s]]->getCeil());
            /* Check whether we're bumping into a wall. */
            if(hole_high < player.getPosition().z + HeadMargin
               || hole_low  > player.getPosition().z - current_eye_height() + KneeHeight) {
                /* Bumps into a wall! Slide along the wall. */
                /* This formula is from Wikipedia article "vector projection". */
                float xd = vVert1.x - vVert0.x;
                float yd = vVert1.y - vVert0.y;
                dx = xd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                dy = yd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                moving = false;
            }
        }
    }

    move_player(dx, dy);
    falling = true;
}

float MapSprite::current_eye_height() {
    return ducking ? DuckHeight : EyeHeight;
}

void MapSprite::move_player(float dx, float dy) {
    Vector3 p = player.getPosition();
    /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, PointSide will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    Sector* sect = loader.getSectors()[player.getSector()];
    auto vert = sect->getVertices();
    for (int s = 0; s < sect->getNPoints(); ++s) {
        Vector2 vPos = { p.x, p.y };
        Vector2 vPosDx = { p.x + dx, p.y + dy };
        Vector2 vVert0 = { vert[s + 0]->x, vert[s + 0]->y };
        Vector2 vVert1 = { vert[s + 1]->x, vert[s + 1]->y };
        bool intersect = intersectBox(vPos, vPosDx, vVert0, vVert1);
        float ps = pointSide(vPosDx, vVert0, vVert1);
        if (sect->getNeighbors()[s] >= 0 && intersect && ps < 0) {
            player.setSector(sect->getNeighbors()[s]);
            break;
        }
    }
    Vector3 diff = { dx, dy, 0 };
    player.setPosition(p + diff);
    player.setAnglesin(sinf(player.getAngle()));
    player.setAnglecos(cosf(player.getAngle()));
}

float MapSprite::yaw(float y, float z) {
    return (y + z * player.getYaw());
}

void MapSprite::draw_vertical_line(Graphics* g,
                                   int x,
                                   int y1,
                                   int y2,
                                   Color top,
                                   Color middle,
                                   Color bottom,
                                   Size windowSize) {
    int ny1 = clamp(y1, 0, windowSize.height - 1);
    int ny2 = clamp(y2, 0, windowSize.height - 1);
    if (ny2 == ny1)
        g->drawPixel(ny1 * windowSize.width + x, middle);
    else if (ny2 > ny1) {
        g->drawPixel(ny1 * windowSize.width + x, top);
        for (int y = ny1 + 1; y < ny2; ++y) {
            g->drawPixel(y * windowSize.width + x, middle);
        }
        g->drawPixel(ny2 * windowSize.width + x, bottom);
    }
}
