struct Clock
{
    float last_tick_time = 0;
    float dt = 0;

    void tick() {
        float tick_time = SDL_GetTicks();
        dt = (tick_time - last_tick_time) / 1000;
        last_tick_time = tick_time;
    }
};