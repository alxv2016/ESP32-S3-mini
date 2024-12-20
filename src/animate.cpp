#include "animate.h"
#include "display.h"

// Global variables and constants
AnimatedGIF gif;
GIFContext gifContext = {&oled, nullptr, 0, 0};  // Context for GIF drawing
const size_t frameBufferSize = GIF_WIDTH * GIF_HEIGHT * 2;  // 2 bytes per pixel (RGB565)

// List of GIF data files and their sizes
GIFData gifFiles[] = {
    { (uint8_t*)LOOK_LEFT_RIGHT_EMOTE, sizeof(LOOK_LEFT_RIGHT_EMOTE) },
    { (uint8_t*)LOOK_UP_DOWN_EMOTE, sizeof(LOOK_UP_DOWN_EMOTE) },
    { (uint8_t*)UWU_EMOTE, sizeof(UWU_EMOTE) },
    { (uint8_t*)SLEEPY_EMOTE, sizeof(SLEEPY_EMOTE) },
    { (uint8_t*)SIGH_EMOTE, sizeof(SIGH_EMOTE) },
    { (uint8_t*)SHOCK_EMOTE, sizeof(SHOCK_EMOTE) },
    { (uint8_t*)PERVE_EMOTE, sizeof(PERVE_EMOTE) },
    { (uint8_t*)MISCHIEF_EMOTE, sizeof(MISCHIEF_EMOTE) },
    { (uint8_t*)LAUGH_EMOTE, sizeof(LAUGH_EMOTE) },
    { (uint8_t*)KISSY_EMOTE, sizeof(KISSY_EMOTE) },
    { (uint8_t*)JUDGE_EMOTE, sizeof(JUDGE_EMOTE) },
    { (uint8_t*)DIZZY_EMOTE, sizeof(DIZZY_EMOTE) },
    { (uint8_t*)CRY_EMOTE, sizeof(CRY_EMOTE) },
    { (uint8_t*)ANGRY_EMOTE, sizeof(ANGRY_EMOTE) },
    // More GIFs can be added here
};

// Function to print memory statistics
void printMemoryStats() {
    Serial.printf("Free heap: %u bytes\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));  // Print free SRAM
    Serial.printf("Free PSRAM: %u bytes\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));  // Print free PSRAM
}

// Function to initialize GIF handling (allocate memory and start GIF object)
void initializeGIF() { 
  gif.begin(BIG_ENDIAN_PIXELS); // Initialize GIF object for drawing with BIG_ENDIAN pixel order
  // Allocate shared frame buffer in PSRAM (only during initialization)
  if (gifContext.sharedFrameBuffer == nullptr) {
    gifContext.sharedFrameBuffer = (uint8_t *)heap_caps_malloc(frameBufferSize, MALLOC_CAP_SPIRAM);  // Allocate frame buffer in PSRAM
    if (!gifContext.sharedFrameBuffer) {
        Serial.println("Error: Failed to allocate shared frame buffer in PSRAM.");  // Handle memory allocation failure
    }
  }
  printMemoryStats(); // Output memory statistics after initialization
}

// Function to clean up GIF context (free allocated memory and close GIF)
void cleanupGIFContext() {
  if (gifContext.sharedFrameBuffer) {
    heap_caps_free(gifContext.sharedFrameBuffer);  // Free allocated memory for frame buffer
    gifContext.sharedFrameBuffer = nullptr;  // Reset pointer to null
  }
  gif.close();  // Close the GIF object to free any associated resources
}

// Helper function to render GIF frames (handles transparency and opacity)
void renderFrame(uint8_t *pixels, uint16_t *palette, uint16_t *buffer, int width, int startX, int y, uint8_t transparent) {
    int x = 0;
    while (x < width) {
        // Render opaque pixels
        int count = 0;
        while (x < width && pixels[x] != transparent) {
            buffer[count++] = palette[pixels[x++]];
        }
        if (count > 0) {
            gifContext.oled->startWrite();
            gifContext.oled->setAddrWindow(startX + x - count, y, count, 1);
            gifContext.oled->writePixels(buffer, count, true, true);
            gifContext.oled->endWrite();
        }

        // Skip transparent pixels
        while (x < width && pixels[x] == transparent) {
            x++;
        }
    }
}

// Draw GIF frame (handles frame rendering)
// Main GIF drawing function
void GIFDraw(GIFDRAW *pDraw) {
    uint8_t *pixels = pDraw->pPixels;
    uint16_t *palette = pDraw->pPalette;
    uint16_t tempBuffer[320]; // Temporary buffer for rendering
    int width = pDraw->iWidth;

    // Clip the width to avoid overflow
    if (width + pDraw->iX > DISPLAY_WIDTH) {
        width = DISPLAY_WIDTH - pDraw->iX;
    }

    // Calculate the Y position
    int y = pDraw->iY + pDraw->y;
    if (y >= DISPLAY_HEIGHT || pDraw->iX >= DISPLAY_WIDTH || width < 1) {
        return;
    }

    // Handle transparency
    if (pDraw->ucHasTransparency) {
        renderFrame(pixels, palette, tempBuffer, width, pDraw->iX, y, pDraw->ucTransparent);
    } else {
        renderFrame(pixels, palette, tempBuffer, width, pDraw->iX, y, 0xFF); // No transparency
    }
}

// Function to play a GIF (with optional looping)
// Play GIF (handle playback of a single GIF)
void playGIF(uint8_t *gifData, size_t gifSize, bool loop = false) {
    if (!gif.open(gifData, gifSize, GIFDraw)) {
        Serial.println("Error: Failed to open GIF file.");
        cleanupGIFContext();
        return;
    }

    size_t currentFrameBufferSize = gif.getCanvasWidth() * (gif.getCanvasHeight() + 2);  // Adjust as needed
    if (gifContext.sharedFrameBuffer == nullptr || currentFrameBufferSize != frameBufferSize) {
        gifContext.sharedFrameBuffer = (uint8_t*)heap_caps_malloc(currentFrameBufferSize, MALLOC_CAP_8BIT);
        if (!gifContext.sharedFrameBuffer) {
            Serial.printf("Memory Error: Failed to allocate %zu bytes\n", currentFrameBufferSize);
            cleanupGIFContext();
            return;
        }
    }

       gif.setDrawType(GIF_DRAW_COOKED);

    const int targetFPS = GIF_FPS;
    const int frameDelay = 1000000 / targetFPS;
    unsigned long previousTime = 0;

    do {
        while (gif.playFrame(false, nullptr)) {
            unsigned long currentTime = micros();
            if (currentTime - previousTime >= frameDelay) {
                previousTime = currentTime;
            } else {
                delayMicroseconds(frameDelay - (currentTime - previousTime));
                previousTime = micros();
            }
        }

        if (loop) {
            gif.reset();
        }
    } while (loop);

    cleanupGIFContext();
}

// Function to play a random GIF from the list
void playRandomGIF() {
  while (true) {
    int randomIndex = random(0, TOTAL_GIFS);  // Get a random index for the GIF list
    uint8_t* gifData = gifFiles[randomIndex].data;  // Get the data for the selected GIF
    size_t gifSize = gifFiles[randomIndex].size;  // Get the size of the selected GIF
    playGIF(gifData, gifSize, false);  // Play the selected GIF once

    unsigned long delayTime = random(2000, 4000);  // Random delay time between GIFs (2 to 4 seconds)
    unsigned long startDelayTime = millis();  // Start the delay timer

    playGIF((uint8_t*)REST_EMOTE, sizeof(REST_EMOTE), false);  // Play a "rest" GIF after the random one

    // Wait for the random delay time before selecting the next GIF
    while (millis() - startDelayTime < delayTime) {
      // Optionally update display or progress bar here
    }
  }
}