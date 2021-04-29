import pygame
from math import *

# Window Setup
windowWidth = 1000
windowHeight = 500
pygame.init()
win = pygame.display.set_mode((windowWidth, windowHeight))
pygame.display.set_caption("TEST")

# Other setup code for your program goes here
pi = 3.1415926
centerx = windowWidth/2
centery = windowHeight/2
connections = 0
bigCircleRadius = 200
bounciness = 5.5
acceleration = 0.25

def dist(x1, y1, x2, y2):
    return sqrt(((x1 - x2) ** 2) + (y1 - y2) ** 2)

class Player:
    def __init__(self, x, y, radius, color):
        self.x = x
        self.y = y
        self.xVel = 0
        self.yVel = 0
        self.radius = radius
        self.color = color
        self.canMove = True
    def draw(self):
        pygame.draw.circle(win, self.color, (self.x, self.y), self.radius)
    def move(self, px, py):
        if dist(500, 250, self.x, self.y) > bigCircleRadius:
            self.canMove = False
        if dist(self.x, self.y, px, py) < 40:
            angle = atan2(py - self.y, px - self.x) + 3.1415926
            self.xVel = cos(angle) * bounciness
            self.yVel = sin(angle) * bounciness
        if self.canMove:
            self.x += self.xVel
            self.y += self.yVel
            

maxVel = 2
incrementVel = 0.05
p1 = Player(360, 250, 20, (0, 255, 0))
p2 = Player(640, 250, 20, (0, 0, 255))

running = True
while running:
    pygame.time.delay(10)
    bigCircleRadius -= 0.01

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    keys=pygame.key.get_pressed()
    if keys[pygame.K_w] and p1.yVel > -maxVel:
        p1.yVel -= acceleration
    if keys[pygame.K_s] and p1.yVel < maxVel:
        p1.yVel += acceleration
    if keys[pygame.K_a] and p1.xVel > -maxVel:
        p1.xVel -= acceleration
    if keys[pygame.K_d] and p1.xVel < maxVel:
        p1.xVel += acceleration
    if keys[pygame.K_UP] and p2.yVel > -maxVel:
        p2.yVel -= acceleration
    if keys[pygame.K_DOWN] and p2.yVel < maxVel:
        p2.yVel += acceleration
    if keys[pygame.K_LEFT] and p2.xVel > -maxVel:
        p2.xVel -= acceleration
    if keys[pygame.K_RIGHT] and p2.xVel < maxVel:
        p2.xVel += acceleration
    if keys[pygame.K_r]:
        p1.x = 360
        p1.y = p2.y = 250
        p2.x = 640
        p1.canMove = True
        p2.canMove = True
        bigCircleRadius = 200

    win.fill((240, 240, 240))

    pygame.draw.circle(win, (255, 100, 100), (500, 250), bigCircleRadius)

    p1.draw()
    pastX = p1.x
    pastY = p1.y
    p1.move(p2.x, p2.y)
    p2.draw()
    p2.move(pastX, pastY)

    if p1.xVel >= incrementVel:
        p1.xVel -= incrementVel
    elif p1.xVel <= - incrementVel:
        p1.xVel += incrementVel
    else:
        p1.xVel = 0

    if p2.xVel >= incrementVel:
        p2.xVel -= incrementVel
    elif p2.xVel <= - incrementVel:
        p2.xVel += incrementVel
    else:
        p2.xVel = 0


    if p1.yVel >= incrementVel:
        p1.yVel -= incrementVel
    elif p1.yVel <= - incrementVel:
        p1.yVel += incrementVel
    else:
        p1.yVel = 0

    if p2.yVel >= incrementVel:
        p2.yVel -= incrementVel
    elif p2.yVel <= - incrementVel:
        p2.yVel += incrementVel
    else:
        p2.yVel = 0

    pygame.display.update()

pygame.quit()
