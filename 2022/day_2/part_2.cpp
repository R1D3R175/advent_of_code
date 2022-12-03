#include <fstream>

static const short ROCK = 0b001, PAPER = 0b010, SCISSORS = 0b100;
static const short LOSE = 0b001, DRAW = 0b010, WIN = 0b100;

int main(int argc, char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    size_t total_score = 0;

    char opponent_move, my_move;
    unsigned short opponent, me;
    while(in >> opponent_move) {
        in >> my_move;

        opponent = 1 << ((int)(opponent_move) - (int)('A'));
        me = 1 << ((int)(my_move) - (int)('X'));

        switch(me) {
            case LOSE:
                me = 1 << ((opponent == ROCK) ? (PAPER) : ((opponent == SCISSORS) ? (ROCK) : (0)));
                break;
            case DRAW:
                me = opponent;
                total_score += 3;
                break;
            case WIN:
                me = 1 << ((opponent != SCISSORS) ? (opponent) : (0));
                total_score += 6;
                break;
        }

        total_score += (me != 4) ? (me) : (me - 1);
    }

    out << total_score << std::endl;

    in.close();
    out.close();
    return 0;
}