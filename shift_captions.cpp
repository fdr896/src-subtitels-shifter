#include <bits/stdc++.h>

using namespace std;

const float SHIFT = /*set how many seconds you want to shift subtitles*/;
const float HOUR = 3600;
const float MINUTE = 60;

void read_time(FILE * file, int & h1, int & m1, float & s1, int & h2, int & m2, float & s2);
float shift_time(int & h, int & m, float & s);
string read_captions(FILE * file);
void write_time(FILE * file, float & begin, float & finish);
inline bool is_blank(char & c);

int main() {
    // if you need you can change input and output files
    FILE * readFile = fopen("INPUT_FILE.srt", "r");
    FILE * writeFile = fopen("OUTPUT_FILE.srt", "w");

    int caption_num;
    while (fscanf(readFile, "%d", &caption_num) == 1) {
        int hours_begin, minutes_begin;
        int hours_finish, minutes_finish;
        float seconds_begin, seconds_finish;

        // read time in appropriate form
        read_time(readFile, hours_begin, minutes_begin, seconds_begin, hours_finish, minutes_finish, seconds_finish);

        // get begin and finish time in seconds and shift it
        float begin = shift_time(hours_begin, minutes_begin, seconds_begin);
        float finish = shift_time(hours_finish, minutes_finish, seconds_finish);

        // get captions
        string captions = read_captions(readFile);


        // write real captions to new file
        fprintf(writeFile, "%d\n", caption_num);
        write_time(writeFile, begin, finish);
        fprintf(writeFile, "%s\n", captions.c_str());
    }
}

void read_time(FILE * file, int & h1, int & m1, float & s1, int & h2, int & m2, float & s2) {
    fscanf(file, "%d:%d:%f --> %d:%d:%f", &h1, &m1, &s1, &h2, &m2, &s2);
}

float shift_time(int & h, int & m, float & s) {
    float result = h * HOUR + m * MINUTE + s;
    return result + SHIFT;
}

string read_captions(FILE * file) {
    string current_captions = "";

    char c;
    while ((c = fgetc(file)) != EOF) {
        if (current_captions.size() && is_blank(c) && is_blank(current_captions.back())) {
            break;
        }

        if (is_blank(c)) {
            c = '\n';
        }

        current_captions.push_back(c);
    }

    current_captions.erase(0, 1);
    return current_captions;
}

void write_time(FILE * file, float & begin, float & finish) {
    int h1 = (int)(begin / HOUR);
    int m1 = (int)((begin - h1 * HOUR) / MINUTE);
    float s1 = begin - h1 * HOUR - m1 * MINUTE;

    int h2 = (int)(finish / HOUR);
    int m2 = (int)((finish - h2 * HOUR) / MINUTE);
    float s2 = finish - h2 * HOUR - m2 * MINUTE;

    fprintf(file, "%d:%d:%0.3f --> %d:%d:%0.3f\n", h1, m1, s1, h2, m2, s2);
}

inline bool is_blank(char & c) {
    return (c == 13) || (c == '\n');
}
