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
#include "../Utils/CQueue.h"

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

    CircularQueue<Item, max_queues> cqueue;

    int ytop[windowSize.width];
    int ybottom[windowSize.width];
    int renderedsectors[loader.getSectors().size()];
    
    //
    for(int x = 0; x < windowSize.width; ++x) ytop[x] = 0;
    for(int x = 0; x < windowSize.width; ++x) ybottom[x] = windowSize.height - 1;
    for(int n = 0; n < loader.getSectors().size(); ++n) renderedsectors[n] = 0;
    //

    cqueue.enque({ player.getSector(), 0, windowSize.width - 1 });
    
    do {
        const Item now = cqueue.deque();
        // 0x21 = 33
        // 0x20 = 32
        if(renderedsectors[now.sectorno] & 0x21) {
            continue; // Odd = still rendering, 0x20 = give up
        }
        ++renderedsectors[now.sectorno];

        Sector *sector = loader.getSectors()[now.sectorno];
        for (int s = 0; s < sector->getNPoints(); s++) {
            // Preparing drawing
            /* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
            Vector3 v1 = *sector->getVertices()[s + 0] - player.getPosition();
            Vector3 v2 = *sector->getVertices()[s + 1] - player.getPosition();
            /* Rotate them around the player's view */
            float pcos = player.getAnglecos();
            float psin = player.getAnglesin();
            Vector2 t1 = {
                v1.x * psin - v1.y * pcos,
                v1.x * pcos + v1.y * psin
            };
            Vector2 t2 = {
                v2.x * psin - v2.y * pcos,
                v2.x * pcos + v2.y * psin
            };
            /* Is the wall at least partially in front of the player? */
            if(t1.y <= 0 && t2.y <= 0) continue;
            /* If it's partially behind the player, clip it against player's view frustrum */
            if(t1.y <= 0 || t2.y <= 0) {
                float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
                // Find an intersection between the wall and the approximate edges of player's view
                Vector2 i1 = intersect(t1, t2, { -nearside, nearz }, { -farside, farz });
                Vector2 i2 = intersect(t1, t2, { nearside, nearz }, { farside, farz });
                if(t1.y < nearz) {
                    if(i1.y > 0) {
                        t1 = {
                            i1.x,
                            i1.y
                        };
                    } else {
                        t1 = {
                            i2.x,
                            i2.y
                        };
                    }
                }
                if(t2.y < nearz) {
                    if(i1.y > 0) {
                        t2 = {
                            i1.x,
                            i1.y
                        };
                    } else {
                        t2 = {
                            i2.x,
                            i2.y
                        };
                    }
                }
            }
            /* Do perspective transformation */
            Vector2 scale1 = {
                hfov(windowSize.height) / t1.y,
                vfov(windowSize.height) / t1.y
            };
            int x1 = windowSize.width/2 - (int)(t1.x * scale1.x);
            Vector2 scale2 = {
                hfov(windowSize.height) / t2.y,
                vfov(windowSize.height) / t2.y
            };
            int x2 = windowSize.width/2 - (int)(t2.x * scale2.x);
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
            int y1a = windowSize.height / 2 - (int)(yaw(yceil, t1.y) * scale1.y);
            int y1b = windowSize.height / 2 - (int)(yaw(yfloor, t1.y) * scale1.y);
            int y2a = windowSize.height / 2 - (int)(yaw(yceil, t2.y) * scale2.y);
            int y2b = windowSize.height / 2 - (int)(yaw(yfloor, t2.y) * scale2.y);
            /* The same for the neighboring sector */
            int ny1a = windowSize.height / 2 - (int)(yaw(nyceil, t1.y) * scale1.y);
            int ny1b = windowSize.height / 2 - (int)(yaw(nyfloor, t1.y) * scale1.y);
            int ny2a = windowSize.height / 2 - (int)(yaw(nyceil, t2.y) * scale2.y);
            int ny2b = windowSize.height / 2 - (int)(yaw(nyfloor, t2.y) * scale2.y);
            /* Render the wall. */
            int beginx = std::max(x1, now.sx1);
            int endx = std::min(x2, now.sx2);
            for(int x = beginx; x <= endx; ++x) {
                /* Calculate the Z coordinate for this point. (Only used for lighting.) */
                int z = ((x - x1) * (t2.y-t1.y) / (x2-x1) + t1.y) * 8;
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
            int queue_position = cqueue.queuePosition(); // This checks the position of the circular queue
    
            if(neighbor >= 0 && endx >= beginx && queue_position) {
                cqueue.enque({ static_cast<unsigned int>(neighbor), beginx, endx });
            }
        }
    // for s in sector's edges
    ++renderedsectors[now.sectorno];
    } while (!cqueue.empty());

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
    const float difference = 0.2f;

    Vector2 mov = { 0, 0 };
    if (key == SDL_SCANCODE_W) {
        mov = mov + (Vector2){
            player.getAnglecos() * difference,
            player.getAnglesin() * difference
        };
        pushing = true;
        handle = true;
    } else if (key == SDL_SCANCODE_S) {
        mov = mov - (Vector2){
            player.getAnglecos() * difference,
            player.getAnglesin() * difference
        };
        pushing = true;
        handle = true;
    }
    if (key == SDL_SCANCODE_A) {
        mov = mov + (Vector2){
            player.getAnglesin() * difference,
            player.getAnglecos() * difference * -1
        };
        pushing = true;
        handle = true;
    } else if (key == SDL_SCANCODE_D) {
        mov = mov + (Vector2){
            player.getAnglesin() * difference * -1,
            player.getAnglecos() * difference
        };
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
                         player.getVelocity().z
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

bool MapSprite::onUI(UI* ui) {
    UIFrameContext context = ui->BeginFrame("Player information");

    ui->CreateText(context, "Player's position {");
    ui->CreateText(context, "\tx = %f", player.getPosition().x);
    ui->CreateText(context, "\ty = %f", player.getPosition().y);
    ui->CreateText(context, "\tz = %f", player.getPosition().z);
    ui->CreateText(context, "}");

    ui->CreateText(context, "Player's velocity {");
    ui->CreateText(context, "\tx = %f", player.getVelocity().x);
    ui->CreateText(context, "\ty = %f", player.getVelocity().y);
    ui->CreateText(context, "\tz = %f", player.getVelocity().z);
    ui->CreateText(context, "}");

    ui->CreateText(context, "Player's angle {");
    ui->CreateText(context, "\tangle = %f", player.getAngle());
    ui->CreateText(context, "\tangleCos = %f", player.getAnglecos());
    ui->CreateText(context, "\tangleSin = %f", player.getAnglesin());
    ui->CreateText(context, "}");
    
    ui->CreateText(context, "Player's yaw = %f", player.getYaw());
    ui->CreateText(context, "Player's sector = %d", player.getSector());
    ui->EndFrame(context);
    return true;
}

bool MapSprite::onKeyRelease(const Key &key) {
    bool handle = false;

    // This is not in the original but I'll leave it to fix the issue with the jump and the drag
    // It is still kind of buggy but it's better than last time.
    player.setVelocity({ player.getVelocity().x / 1.5f,
                         player.getVelocity().y / 1.5f,
                         player.getVelocity().z / 1.5f
    });
    if (key == SDL_SCANCODE_SPACE && !ground && abs(player.getVelocity().z) > 0.01f) {
        handle_falling();
        return false;
    }
    moving = true;
    if (abs(player.getVelocity().x) < 0.0001f &&
        abs(player.getVelocity().y) < 0.0001f &&
        abs(player.getVelocity().z ) < 0.0001f) {
        player.setVelocity({ 0.0f,
                             0.0f,
                            0.0f
        });
        handle = true;
    }
    //
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
        g->drawPoint({ x, ny1 }, middle);
    else if (ny2 > ny1) {
        g->drawPoint({ x, ny1 }, top);
        g->drawLine({ x, ny1 + 1 }, { x, ny2 - 1 }, middle);
        g->drawPoint({ x, ny2 }, bottom);
    }
}
