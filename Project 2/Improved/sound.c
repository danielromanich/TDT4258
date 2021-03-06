#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sound.h"
#include "timer.h"
#include "dac.h"

int DISABLE_SLEEP = 0b010;	//Normal energy mode
int ENABLE_SLEEP = 0b110;	//Energy mode = deep sleep

Song *currentSong;

uint16_t currentNoteLen;
uint32_t i = 0;
uint16_t songProgress = 0;
uint16_t progress = 0;

void initSong()
{
    chooseSong(&GOT, 0x3400);
}

void setNote(Note * note, int offset)
{
    *DAC0_CH0DATA = note->length[offset];	//Set left volume
    *DAC0_CH1DATA = note->length[offset];	//Set right volume
} 
 
 
void chooseSong(Song *song, uint16_t length)
{
    currentSong = song;
    currentNoteLen = length;
    setSleep(DISABLE_SLEEP);
    setupDAC();
    setupTimer(SAMPLE_PERIOD);
}
 
void setSleep(int em)
{
    *SCR = em;
}
 
void stopSong()
{
    progress = 0;
    songProgress = 0;
    i = 0;
    disableTimer();
    disableDAC();
    setSleep(ENABLE_SLEEP);
}


Note D3 = {300, {128, 130, 133, 136, 138, 141, 144, 146, 149, 151, 154, 157, 159, 162, 164, 167, 169, 172, 175, 177, 179, 182, 184, 187, 189, 191, 194, 196, 198, 200, 203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 222, 224, 226, 228, 229, 231, 232, 234, 235, 237, 238, 239, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 251, 252, 253, 253, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 253, 252, 252, 251, 250, 249, 249, 248, 247, 246, 245, 244, 242, 241, 240, 239, 237, 236, 235, 233, 231, 230, 228, 227, 225, 223, 221, 219, 218, 216, 214, 212, 210, 208, 206, 203, 201, 199, 197, 195, 192, 190, 188, 185, 183, 180, 178, 175, 173, 170, 168, 165, 163, 160, 158, 155, 152, 150, 147, 145, 142, 139, 137, 134, 131, 129, 126, 123, 121, 118, 115, 113, 110, 107, 105, 102, 99, 97, 94, 92, 89, 87, 84, 81, 79, 77, 74, 72, 69, 67, 65, 62, 60, 58, 55, 53, 51, 49, 47, 45, 43, 41, 39, 37, 35, 33, 31, 30, 28, 26, 25, 23, 22, 20, 19, 17, 16, 15, 13, 12, 11, 10, 9, 8, 7, 6, 5, 5, 4, 3, 3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 3, 3, 4, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17, 18, 20, 21, 23, 24, 26, 28, 29, 31, 33, 35, 37, 39, 40, 42, 44, 47, 49, 51, 53, 55, 57, 60, 62, 64, 66, 69, 71, 74, 76, 79, 81, 84, 86, 89, 91, 94, 96, 99, 102, 104, 107, 109, 112, 115, 117, 120, 123}};
Note D5 = {75, {128, 138, 149, 159, 169, 179, 189, 198, 207, 215, 222, 229, 235, 241, 245, 249, 252, 254, 255, 255, 255, 253, 251, 248, 244, 239, 233, 227, 219, 212, 203, 195, 185, 175, 165, 155, 145, 134, 123, 113, 102, 92, 81, 72, 62, 53, 45, 37, 30, 23, 17, 12, 8, 5, 2, 0, 0, 0, 1, 3, 5, 9, 13, 18, 24, 31, 39, 47, 55, 64, 74, 84, 94, 104, 115}};
Note D4 = {150, {128, 133, 138, 144, 149, 154, 159, 164, 169, 175, 179, 184, 189, 194, 198, 203, 207, 211, 215, 219, 222, 226, 229, 232, 235, 238, 241, 243, 245, 247, 249, 251, 252, 253, 254, 255, 255, 255, 255, 255, 255, 254, 253, 252, 251, 249, 248, 246, 244, 241, 239, 236, 233, 230, 227, 223, 219, 216, 212, 208, 203, 199, 195, 190, 185, 180, 175, 170, 165, 160, 155, 150, 145, 139, 134, 129, 123, 118, 113, 107, 102, 97, 92, 87, 81, 77, 72, 67, 62, 58, 53, 49, 45, 41, 37, 33, 30, 26, 23, 20, 17, 15, 12, 10, 8, 6, 5, 3, 2, 1, 0, 0, 0, 0, 0, 0, 1, 1, 3, 4, 5, 7, 9, 11, 13, 16, 18, 21, 24, 28, 31, 35, 39, 42, 47, 51, 55, 60, 64, 69, 74, 79, 84, 89, 94, 99, 104, 109, 115, 120}};
Note B3 = {178, {128, 132, 136, 141, 145, 150, 154, 159, 163, 167, 172, 176, 180, 184, 188, 192, 196, 199, 203, 207, 210, 214, 217, 220, 223, 226, 229, 232, 234, 236, 239, 241, 243, 245, 247, 248, 250, 251, 252, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 254, 253, 252, 251, 250, 249, 247, 246, 244, 242, 240, 237, 235, 233, 230, 227, 224, 221, 218, 215, 212, 208, 205, 201, 197, 194, 190, 186, 182, 177, 173, 169, 165, 161, 156, 152, 147, 143, 138, 134, 129, 125, 120, 116, 111, 107, 103, 98, 94, 90, 85, 81, 77, 73, 69, 65, 61, 57, 53, 50, 46, 43, 39, 36, 33, 30, 27, 25, 22, 20, 17, 15, 13, 11, 9, 8, 6, 5, 3, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 6, 7, 9, 10, 12, 14, 17, 19, 21, 24, 27, 29, 32, 35, 39, 42, 45, 49, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 93, 97, 101, 106, 110, 115, 119}};
Note FS5 = {59, {128, 141, 154, 167, 180, 192, 203, 214, 223, 231, 239, 245, 249, 253, 255, 255, 255, 252, 249, 244, 238, 230, 222, 212, 201, 190, 178, 165, 152, 139, 125, 112, 99, 86, 73, 61, 50, 40, 31, 22, 15, 9, 5, 2, 0, 0, 1, 3, 7, 12, 18, 26, 35, 45, 55, 67, 79, 92, 105}};
Note FS4 = {119, {128, 134, 141, 148, 154, 161, 167, 174, 180, 186, 192, 198, 203, 208, 214, 218, 223, 227, 231, 235, 239, 242, 245, 247, 249, 251, 253, 254, 255, 255, 255, 255, 255, 254, 252, 251, 249, 247, 244, 241, 238, 234, 230, 226, 222, 217, 212, 207, 201, 196, 190, 184, 178, 172, 165, 159, 152, 146, 139, 132, 125, 119, 112, 105, 99, 92, 86, 79, 73, 67, 61, 56, 50, 45, 40, 35, 31, 26, 22, 19, 15, 12, 9, 7, 5, 3, 2, 1, 0, 0, 0, 0, 1, 2, 3, 5, 7, 9, 12, 15, 18, 22, 26, 30, 35, 40, 45, 50, 55, 61, 67, 73, 79, 85, 92, 98, 105, 112, 118}};
Note FS3 = {238, {128, 131, 134, 138, 141, 144, 148, 151, 154, 158, 161, 164, 167, 170, 174, 177, 180, 183, 186, 189, 192, 195, 198, 200, 203, 206, 208, 211, 214, 216, 218, 221, 223, 225, 227, 229, 231, 233, 235, 237, 239, 240, 242, 243, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 252, 252, 251, 250, 249, 248, 247, 245, 244, 242, 241, 239, 238, 236, 234, 232, 230, 228, 226, 224, 222, 219, 217, 214, 212, 209, 207, 204, 201, 199, 196, 193, 190, 187, 184, 181, 178, 175, 172, 168, 165, 162, 159, 155, 152, 149, 146, 142, 139, 135, 132, 129, 125, 122, 119, 115, 112, 109, 105, 102, 99, 95, 92, 89, 86, 83, 79, 76, 73, 70, 67, 64, 61, 58, 56, 53, 50, 48, 45, 42, 40, 37, 35, 33, 31, 28, 26, 24, 22, 20, 19, 17, 15, 14, 12, 11, 9, 8, 7, 6, 5, 4, 3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 14, 15, 17, 18, 20, 22, 24, 26, 28, 30, 33, 35, 37, 40, 42, 45, 47, 50, 53, 55, 58, 61, 64, 67, 70, 73, 76, 79, 82, 85, 89, 92, 95, 98, 102, 105, 108, 112, 115, 118, 122}};
Note B5 = {44, {128, 145, 163, 180, 196, 210, 223, 234, 243, 250, 254, 255, 255, 251, 246, 237, 227, 215, 201, 186, 169, 152, 134, 116, 98, 81, 65, 50, 36, 25, 15, 8, 2, 0, 0, 2, 7, 14, 24, 35, 49, 64, 80, 97}};
Note B4 = {89, {128, 136, 145, 154, 163, 172, 180, 188, 196, 203, 210, 217, 223, 229, 234, 239, 243, 247, 250, 252, 254, 255, 255, 255, 255, 253, 251, 249, 246, 242, 237, 233, 227, 221, 215, 208, 201, 194, 186, 177, 169, 161, 152, 143, 134, 125, 116, 107, 98, 90, 81, 73, 65, 57, 50, 43, 36, 30, 25, 20, 15, 11, 8, 5, 2, 1, 0, 0, 0, 1, 2, 4, 7, 10, 14, 19, 24, 29, 35, 42, 49, 56, 64, 72, 80, 88, 97, 106, 115}};
Note F5 = {63, {128, 140, 153, 165, 177, 189, 199, 210, 219, 227, 235, 241, 246, 251, 253, 255, 255, 255, 252, 249, 245, 239, 232, 224, 215, 206, 195, 184, 173, 160, 148, 135, 123, 110, 97, 85, 73, 62, 52, 42, 33, 25, 18, 12, 7, 3, 1, 0, 0, 1, 4, 8, 13, 19, 26, 34, 43, 53, 64, 75, 87, 99, 112}};
Note F4 = {126, {128, 134, 140, 147, 153, 159, 165, 171, 177, 183, 189, 194, 199, 205, 210, 214, 219, 223, 227, 231, 235, 238, 241, 244, 246, 249, 251, 252, 253, 254, 255, 255, 255, 255, 255, 254, 252, 251, 249, 247, 245, 242, 239, 236, 232, 228, 224, 220, 215, 211, 206, 201, 195, 190, 184, 178, 173, 166, 160, 154, 148, 142, 135, 129, 123, 116, 110, 104, 97, 91, 85, 79, 73, 68, 62, 57, 52, 47, 42, 37, 33, 29, 25, 21, 18, 15, 12, 9, 7, 5, 3, 2, 1, 0, 0, 0, 0, 0, 1, 2, 4, 5, 8, 10, 13, 15, 19, 22, 26, 30, 34, 39, 43, 48, 53, 58, 64, 70, 75, 81, 87, 93, 99, 106, 112, 118}};
Note F3 = {252, {128, 131, 134, 137, 140, 143, 147, 150, 153, 156, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 189, 191, 194, 197, 199, 202, 205, 207, 210, 212, 214, 217, 219, 221, 223, 225, 227, 229, 231, 233, 235, 236, 238, 240, 241, 243, 244, 245, 246, 248, 249, 250, 251, 251, 252, 253, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 252, 252, 251, 250, 249, 248, 247, 246, 245, 243, 242, 240, 239, 237, 236, 234, 232, 230, 228, 226, 224, 222, 220, 218, 215, 213, 211, 208, 206, 203, 201, 198, 195, 193, 190, 187, 184, 181, 178, 175, 173, 170, 167, 163, 160, 157, 154, 151, 148, 145, 142, 139, 135, 132, 129, 126, 123, 119, 116, 113, 110, 107, 104, 101, 97, 94, 91, 88, 85, 82, 79, 76, 73, 71, 68, 65, 62, 60, 57, 54, 52, 49, 47, 44, 42, 39, 37, 35, 33, 31, 29, 27, 25, 23, 21, 19, 18, 16, 15, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 4, 5, 5, 6, 7, 9, 10, 11, 13, 14, 15, 17, 19, 20, 22, 24, 26, 28, 30, 32, 34, 36, 39, 41, 43, 46, 48, 51, 53, 56, 58, 61, 64, 67, 70, 72, 75, 78, 81, 84, 87, 90, 93, 96, 99, 102, 106, 109, 112, 115, 118, 121}};
Note CS4 = {159, {128, 133, 138, 143, 148, 153, 158, 162, 167, 172, 177, 181, 186, 190, 195, 199, 203, 207, 211, 215, 218, 222, 225, 228, 231, 234, 237, 239, 242, 244, 246, 248, 249, 251, 252, 253, 254, 255, 255, 255, 255, 255, 255, 255, 254, 253, 252, 250, 249, 247, 245, 243, 241, 239, 236, 233, 230, 227, 224, 221, 217, 213, 210, 206, 202, 197, 193, 189, 184, 180, 175, 170, 166, 161, 156, 151, 146, 141, 136, 131, 126, 121, 116, 111, 106, 101, 96, 91, 86, 81, 77, 72, 68, 63, 59, 55, 51, 47, 43, 39, 36, 32, 29, 26, 23, 20, 17, 15, 12, 10, 8, 7, 5, 4, 2, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 2, 4, 5, 7, 8, 10, 12, 15, 17, 20, 23, 26, 29, 32, 36, 39, 43, 47, 51, 55, 59, 63, 68, 72, 77, 81, 86, 91, 96, 101, 106, 111, 116, 121}};
Note CS5 = {79, {128, 138, 148, 158, 167, 177, 186, 195, 203, 211, 218, 225, 231, 237, 242, 246, 249, 252, 254, 255, 255, 255, 254, 252, 249, 245, 241, 236, 230, 224, 217, 210, 202, 193, 184, 175, 166, 156, 146, 136, 126, 116, 106, 96, 86, 77, 68, 59, 51, 43, 36, 29, 23, 17, 12, 8, 5, 2, 1, 0, 0, 0, 2, 4, 7, 10, 15, 20, 26, 32, 39, 47, 55, 63, 72, 81, 91, 101, 111}};
Note AS4 = {94, {128, 136, 144, 153, 161, 169, 177, 185, 192, 199, 206, 213, 219, 225, 230, 235, 239, 243, 247, 249, 252, 253, 255, 255, 255, 255, 254, 252, 250, 248, 244, 241, 237, 232, 227, 221, 215, 209, 202, 195, 188, 180, 172, 164, 156, 148, 139, 131, 122, 114, 105, 97, 89, 81, 73, 65, 58, 51, 45, 38, 32, 27, 22, 17, 13, 10, 7, 4, 2, 1, 0, 0, 0, 1, 2, 4, 6, 9, 13, 17, 21, 26, 32, 38, 44, 50, 57, 65, 72, 80, 88, 96, 104, 113}};
Note C4 = {168, {128, 132, 137, 142, 146, 151, 156, 160, 165, 170, 174, 178, 183, 187, 191, 195, 199, 203, 207, 211, 214, 218, 221, 224, 227, 230, 233, 236, 238, 240, 243, 245, 246, 248, 250, 251, 252, 253, 254, 255, 255, 255, 255, 255, 255, 255, 254, 253, 253, 251, 250, 249, 247, 245, 243, 241, 239, 237, 234, 231, 228, 225, 222, 219, 216, 212, 208, 205, 201, 197, 193, 189, 185, 180, 176, 171, 167, 162, 158, 153, 148, 144, 139, 134, 129, 125, 120, 115, 110, 106, 101, 96, 92, 87, 83, 78, 74, 70, 65, 61, 57, 53, 50, 46, 42, 39, 35, 32, 29, 26, 23, 20, 18, 16, 13, 11, 9, 8, 6, 5, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 6, 7, 9, 11, 13, 15, 17, 20, 23, 25, 28, 31, 35, 38, 41, 45, 49, 53, 56, 60, 65, 69, 73, 77, 82, 86, 91, 95, 100, 105, 109, 114, 119}};
Note C5 = {84, {128, 137, 146, 156, 165, 174, 183, 191, 199, 207, 214, 221, 227, 233, 238, 243, 246, 250, 252, 254, 255, 255, 255, 254, 253, 250, 247, 243, 239, 234, 228, 222, 216, 208, 201, 193, 185, 176, 167, 158, 148, 139, 129, 120, 110, 101, 92, 83, 74, 65, 57, 50, 42, 35, 29, 23, 18, 13, 9, 6, 3, 1, 0, 0, 0, 1, 2, 4, 7, 11, 15, 20, 25, 31, 38, 45, 53, 60, 69, 77, 86, 95, 105, 114}};
Note C6 = {42, {128, 146, 165, 183, 199, 214, 227, 238, 246, 252, 255, 255, 253, 247, 239, 228, 216, 201, 185, 167, 148, 129, 110, 92, 74, 57, 42, 29, 18, 9, 3, 0, 0, 2, 7, 15, 25, 38, 53, 69, 86, 105}};
Note E4 = {133, {128, 134, 139, 145, 151, 157, 163, 169, 174, 180, 185, 191, 196, 201, 206, 210, 215, 219, 223, 227, 231, 234, 237, 240, 243, 245, 248, 250, 251, 253, 254, 255, 255, 255, 255, 255, 255, 254, 253, 251, 250, 248, 245, 243, 240, 237, 234, 231, 227, 223, 219, 215, 210, 206, 201, 196, 191, 185, 180, 174, 169, 163, 157, 151, 145, 139, 133, 127, 121, 115, 109, 104, 98, 92, 86, 81, 75, 70, 64, 59, 54, 49, 45, 40, 36, 32, 28, 24, 21, 18, 15, 12, 10, 7, 5, 4, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 4, 5, 7, 10, 12, 15, 18, 21, 24, 28, 32, 36, 40, 45, 49, 54, 59, 64, 70, 75, 81, 86, 92, 98, 104, 110, 116}};
Note C7 = {21, {128, 165, 199, 227, 246, 255, 253, 239, 216, 185, 148, 110, 74, 42, 18, 3, 0, 7, 25, 53, 86}};
Note E5 = {66, {128, 139, 151, 163, 174, 185, 196, 206, 215, 223, 231, 237, 243, 248, 251, 254, 255, 255, 255, 253, 250, 245, 240, 234, 227, 219, 210, 201, 191, 180, 169, 157, 145, 133, 121, 109, 98, 86, 75, 64, 54, 45, 36, 28, 21, 15, 10, 5, 2, 0, 0, 0, 1, 4, 7, 12, 18, 24, 32, 40, 49, 59, 70, 81, 92, 104}};
Note E6 = {33, {128, 151, 174, 196, 215, 231, 243, 251, 255, 255, 250, 240, 227, 210, 191, 169, 145, 121, 98, 75, 54, 36, 21, 10, 2, 0, 1, 7, 18, 32, 49, 70, 92}};
Note E7 = {16, {128, 174, 215, 243, 255, 250, 227, 191, 145, 98, 54, 21, 2, 1, 18, 49}};
Note A3 = {200, {128, 132, 136, 140, 143, 147, 151, 155, 159, 163, 167, 171, 174, 178, 182, 185, 189, 192, 196, 199, 202, 206, 209, 212, 215, 218, 221, 223, 226, 228, 231, 233, 235, 237, 239, 241, 243, 245, 246, 248, 249, 250, 251, 252, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 254, 253, 253, 252, 251, 250, 248, 247, 245, 244, 242, 240, 238, 236, 234, 232, 229, 227, 224, 222, 219, 216, 213, 210, 207, 204, 200, 197, 194, 190, 187, 183, 180, 176, 172, 168, 165, 161, 157, 153, 149, 145, 141, 137, 133, 129, 125, 121, 117, 113, 109, 105, 101, 97, 93, 90, 86, 82, 78, 75, 71, 67, 64, 60, 57, 54, 50, 47, 44, 41, 38, 35, 33, 30, 28, 25, 23, 20, 18, 16, 14, 13, 11, 9, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 9, 11, 12, 14, 16, 18, 20, 22, 25, 27, 30, 32, 35, 38, 41, 44, 47, 50, 53, 57, 60, 63, 67, 70, 74, 78, 81, 85, 89, 93, 97, 101, 105, 109, 113, 117, 121}};
Note A4 = {100, {128, 136, 143, 151, 159, 167, 174, 182, 189, 196, 202, 209, 215, 221, 226, 231, 235, 239, 243, 246, 249, 251, 253, 254, 255, 255, 255, 255, 253, 252, 250, 247, 244, 240, 236, 232, 227, 222, 216, 210, 204, 197, 190, 183, 176, 168, 161, 153, 145, 137, 129, 121, 113, 105, 97, 90, 82, 75, 67, 60, 54, 47, 41, 35, 30, 25, 20, 16, 13, 9, 6, 4, 2, 1, 0, 0, 0, 0, 1, 3, 5, 8, 11, 14, 18, 22, 27, 32, 38, 44, 50, 57, 63, 70, 78, 85, 93, 101, 109, 117}};
Note A5 = {50, {128, 143, 159, 174, 189, 202, 215, 226, 235, 243, 249, 253, 255, 255, 253, 250, 244, 236, 227, 216, 204, 190, 176, 161, 145, 129, 113, 97, 82, 67, 54, 41, 30, 20, 13, 6, 2, 0, 0, 1, 5, 11, 18, 27, 38, 50, 63, 78, 93, 109}};
Note G3 = {225, {128, 131, 135, 138, 142, 145, 149, 152, 156, 159, 163, 166, 170, 173, 176, 179, 183, 186, 189, 192, 195, 198, 201, 204, 207, 210, 212, 215, 218, 220, 223, 225, 227, 229, 231, 234, 235, 237, 239, 241, 242, 244, 245, 247, 248, 249, 250, 251, 252, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 253, 252, 251, 250, 249, 248, 246, 245, 243, 242, 240, 239, 237, 235, 233, 231, 229, 226, 224, 222, 219, 217, 214, 211, 209, 206, 203, 200, 197, 194, 191, 188, 185, 182, 178, 175, 172, 168, 165, 162, 158, 155, 151, 148, 144, 141, 137, 133, 130, 126, 123, 119, 116, 112, 109, 105, 101, 98, 95, 91, 88, 84, 81, 78, 74, 71, 68, 65, 62, 59, 56, 53, 50, 47, 44, 42, 39, 37, 34, 32, 29, 27, 25, 23, 21, 19, 17, 15, 14, 12, 11, 9, 8, 7, 5, 4, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 4, 5, 7, 8, 9, 11, 12, 14, 15, 17, 19, 21, 23, 25, 27, 29, 32, 34, 37, 39, 42, 44, 47, 50, 53, 56, 59, 62, 65, 68, 71, 74, 78, 81, 84, 88, 91, 95, 98, 102, 105, 109, 112, 116, 119, 123}};
Note G4 = {112, {128, 135, 142, 149, 156, 163, 170, 176, 183, 189, 195, 201, 207, 212, 218, 223, 227, 231, 235, 239, 242, 245, 248, 250, 252, 254, 255, 255, 255, 255, 255, 254, 253, 251, 249, 246, 243, 240, 237, 233, 229, 224, 219, 214, 209, 203, 197, 191, 185, 178, 172, 165, 158, 151, 144, 137, 130, 123, 116, 109, 101, 95, 88, 81, 74, 68, 62, 56, 50, 44, 39, 34, 29, 25, 21, 17, 14, 11, 8, 5, 4, 2, 1, 0, 0, 0, 0, 1, 2, 4, 5, 8, 11, 14, 17, 21, 25, 29, 34, 39, 44, 50, 56, 62, 68, 74, 81, 88, 95, 102, 109, 116}};
Note G5 = {56, {128, 142, 156, 170, 183, 195, 207, 218, 227, 235, 242, 248, 252, 255, 255, 255, 253, 249, 243, 237, 229, 219, 209, 197, 185, 172, 158, 144, 130, 116, 102, 88, 74, 62, 50, 39, 29, 21, 14, 8, 4, 1, 0, 0, 2, 5, 11, 17, 25, 34, 44, 56, 68, 81, 95, 109}};
Note G6 = {28, {128, 156, 183, 207, 227, 242, 252, 255, 253, 243, 229, 209, 185, 158, 130, 102, 74, 50, 29, 14, 4, 0, 2, 11, 25, 44, 68, 95}};
Note G7 = {14, {128, 183, 227, 252, 253, 229, 185, 130, 74, 29, 4, 2, 25, 68}};

Song GOT = {152, {&E5, &E5, &A4, &A4, &C5, &D5, &E5, &E5, &A4, &A4, &C5, &D5, &E5, &E5, &A4, &A4, &C5, &D5, &E5, &E5, &A4, &A4, &C5, &D5, &E5, &E5, &A4, &A4, &CS5, &D5, &E5, &E5, &A4, &A4, &CS5, &D5, &E5, &E5, &A4, &A4, &CS5, &D5, &E5, &E5, &A4, &A4, &CS5, &D5, &E5, &E5, &E5, &E5, &E5, &E5, &A4, &A4, &A4, &A4, &A4, &A4, &C5, &D5, &E5, &E5, &E5, &E5, &A4, &A4, &A4, &A4, &C5, &D5, &B4, &B4, &E4, &E4, &G4, &A4, &B4, &B4, &E4, &E4, &G4, &A4, &B4, &B4, &E4, &E4, &G4, &A4, &B4, &B4, &E4, &E4, &G4, &A4, &D5, &D5, &D5, &D5, &D5, &D5, &G4, &G4, &G4, &G4, &G4, &G4, &C5, &B4, &D5, &D5, &D5, &D5, &G4, &G4, &G4, &G4, &C5, &B4, &A4, &A4, &D4, &D4, &F4, &G4, &A4, &A4, &D4, &D4, &F4, &G4, &A4, &A4, &D4, &D4, &F4, &G4, &A4, &A4, &D4, &D4, &F4, &G4, &A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4}};
Song SHOOTING = {60, {&E5, &E5, &E5, &E5, &E5, &E5, &A4, &A4, &F5, &F5, &F5, &F5, &C5, &C5, &A4, &E5, &E5, &E5, &E5, &E5, &E5, &A4, &A4, &F5, &F5, &F5, &F5, &C5, &C5, &A4, &E5, &E5, &E5, &E5, &E5, &E5, &A4, &A4, &F5, &F5, &F5, &F5, &C5, &C5, &A4, &E5, &E5, &E5, &E5, &E5, &E5, &A4, &A4, &F5, &F5, &E5, &E5, &C5, &C5, &A4 }};
Song OUT = {3 , {&B4, &B3, &B4}};
Song PONG = {2, {&C4, &C4}};
Song PING = {2, {&C6, &C6}};
Song WALL = {2, {&C5, &C5}};