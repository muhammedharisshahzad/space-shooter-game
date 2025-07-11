#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <fstream>
using namespace std;

class FileHandling
{
    private:
        ifstream read_file;
        ofstream write_file;
        int temp;
    public:
        int read_score()
        {
            read_file.open("HighScore.txt");
            read_file >> temp;
            read_file.close();
            return temp;
        }
        void update_score(int score)
        {
            write_file.open("HighScore.txt");
            write_file << score;
            write_file.close();
        }
};

#endif