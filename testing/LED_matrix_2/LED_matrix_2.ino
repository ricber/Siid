#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// we define the pin that our NeoPixel panel is plugged into
#define PIN 2

// define constants
int DELAY = 50; // in ms

// we initialize our 8×8 matrix using the NeoMatrix library
Adafruit_NeoMatrix matrix =
    Adafruit_NeoMatrix(8,
                       8,
                       PIN,
                       NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS
                           + NEO_MATRIX_ZIGZAG,
                       NEO_GRB + NEO_KHZ800);

struct RGB
{
    byte r;
    byte g;
    byte b;
};

typedef struct Eye_
{
    int v1;
    int v2;
    int v3;
    int v4;
    int v5;
    int v6;
    int v7;
    int v8;
} Eye; // some struct


// Define some colors we'll use frequently
RGB vanillia = {225, 206, 154}; // neutral 254,254,226
RGB red      = {254, 27, 0};    // angry
RGB yellow   = {255, 215, 0};   // happy
RGB blue     = {116, 208, 241}; // sadness
RGB green    = {112, 141, 35};  // disgust
RGB purple   = {75, 0, 130};    // fair
RGB off      = {0, 0, 0};


// Check the pixel one after another and fill them if necessary
void
drawEye(int eye[8][8], RGB color)
{
    for (uint16_t row = 0; row < 8; row++)
    {
        for (uint16_t column = 0; column < 8; column++)
        {
            if (eye[row][column] == 1)
            {
                matrix.drawPixel(column,
                                 row,
                                 matrix.Color(color.r, color.g, color.b));
                matrix.show();
                delay(DELAY);
            }
        }
    }
}

void
eyesInlight(int emotion)
{
    /*
   //Define variable
   int eye[8][8] = {0} ;// table define the eye matrix
    */

    // Define emotions
    int const angry[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                             {1, 0, 0, 0, 0, 0, 0, 1},
                             {0, 1, 0, 0, 0, 0, 1, 0},
                             {0, 0, 1, 0, 0, 1, 0, 0},
                             {0, 0, 0, 1, 1, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0}};

    int const happy1[8][8] = {
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };
    int const happy2[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };
    int const happy3[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };
    int const happy4[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 1, 1, 1, 1, 0, 0},
                              {0, 1, 1, 1, 1, 1, 1, 0},
                              {1, 1, 0, 0, 0, 0, 1, 1},
                              {1, 0, 0, 0, 0, 0, 0, 1},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}};

    int const sadness1[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 1, 1, 1, 1, 1, 1, 0},
                                {1, 1, 1, 1, 1, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {1, 1, 1, 1, 1, 1, 1, 1},
                                {0, 1, 1, 1, 1, 1, 1, 0},
                                {0, 0, 1, 1, 1, 1, 0, 0}};

    int const sadness2[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 1, 1, 1, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {1, 1, 1, 1, 1, 1, 1, 1},
                                {0, 1, 1, 1, 1, 1, 1, 0},
                                {0, 0, 1, 1, 1, 1, 0, 0}};
    int const sadness2[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 1, 1, 1, 1, 1, 1, 0},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {0, 1, 1, 1, 1, 1, 1, 0},
                                {0, 0, 1, 1, 1, 1, 0, 0}};

    int const sadness[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0},
                               {1, 0, 0, 0, 0, 0, 0, 1},
                               {1, 1, 0, 0, 0, 0, 1, 1},
                               {0, 1, 1, 1, 1, 1, 1, 0},
                               {0, 0, 1, 1, 1, 1, 0, 0}};

    int const fear[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 1, 1, 0, 0, 0},
                            {0, 0, 0, 1, 1, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0}};

    int const disgust[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 1, 1, 1, 0, 0, 0},
                               {0, 0, 0, 0, 1, 1, 1, 0},
                               {0, 0, 0, 0, 0, 0, 1, 1},
                               {0, 0, 0, 0, 1, 1, 1, 0},
                               {0, 0, 1, 1, 1, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0}};

    int const neutral1[8][8] = {{0, 0, 1, 1, 1, 1, 0, 0},
                                {0, 1, 1, 1, 1, 1, 1, 0},
                                {1, 1, 1, 1, 1, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {1, 1, 1, 1, 1, 1, 1, 1},
                                {0, 1, 1, 1, 1, 1, 1, 0},
                                {0, 0, 1, 1, 1, 1, 0, 0}};

    int const neutral2[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 1, 1, 1, 1, 1, 1, 0},
                                {1, 1, 1, 1, 1, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {1, 1, 1, 1, 1, 1, 1, 1},
                                {0, 1, 1, 1, 1, 1, 1, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0}};

    int const neutral3[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 1, 1, 1, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {1, 1, 1, 1, 1, 1, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0}};

    int const neutral4[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {1, 1, 1, 0, 0, 1, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0}};


    int const turned_off[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0}};

    /*########## !!!!!!! TODO:
     *
     * substitute this if-else with a switch-case
     *
     * 0 neutral
     * 1 happy
     * 2 angry
     * 3 sadness
     * 4 fear
     * 5 disgust
     *
     * we also have to define the corresponding color
     *
     * use the fillMatrix function instead to use turned_off matrix
     *
     *!!!!!!!! ##########*/

    switch (emotion)
    {
    case 0:
        drawEye(neutral1, vanillia);
        delay(DELAY_EYE);
        drawEye(neutral2, vanillia);
        delay(DELAY_EYE);
        drawEye(neutral3, vanillia);
        delay(DELAY_EYE);
        drawEye(neutral4, vanillia);
        delay(DELAY_EYE);
        drawEye(turnedoff, vanillia);
        delay(DELAY_EYE);
        drawEye(neutral4, vanillia);
        delay(DELAY_EYE);
        drawEye(neutral3, vanillia);
        delay(DELAY_EYE);
        drawEye(neutral2, vanillia);
        delay(DELAY_EYE);
        drawEye(neutral1, vanillia);
        break;
    case 1:
        drawEye(neutral1, yellow);
        delay(DELAY_EYE);
        drawEye(happy1, yellow);
        delay(DELAY_EYE);
        drawEye(happy2, yellow);
        delay(DELAY_EYE);
        drawEye(happy3, yellow);
        delay(DELAY_EYE);
        drawEye(happy4, yellow);
        delay(DELAY_EYE);
        break;
    case 2:
        drawEye(angry, red);
        break;
    case 3:
        drawEye(sadness, red);
        break;
    case 4:
        drawEye(fear, red);
        break;
    case 5:
        drawEye(disgust, red);
        break;
    default:
        drawEye(turned_off, red);
        break;
    }
}
/* eye = {
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 0, 0, 0, 0, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 1, 0}
 };// To make the eye cry

 fear with quick blink*/


void
setup()
{
    // we initialize the matrix and configure its pixel brightness, text color
    // and text wrapping options
    matrix.begin();
    matrix.setBrightness(5);
    matrix.setTextColor(matrix.Color(255, 255, 255));
    matrix.setTextWrap(false);

    /* TO TEST the consumption of the matrix with all LED turned on I used the
     * following instructions
     *  matrix.fillScreen(matrix.Color(red.r, red.g, red.b));
     *  matrix.show();
    */
}

void
loop()
{
    eyesInlight(2);
}
