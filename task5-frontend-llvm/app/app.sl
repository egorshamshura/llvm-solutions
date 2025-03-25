func main() -> int {
    for (int step = 0; step < 1000; ++step) {
        for (int y = 0; y < 256; ++y) {
            for (int x = 0; x < 512; ++x) {
                simPutPixel(x, y, 4278190080 + x * y * step);
            }
        }
        simFlush();
    }
    return 0;
}