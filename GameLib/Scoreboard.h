/**
 * @file Scoreboard.h
 * @author Tyler McDonald
 *
 * Contains the declaration for our Scoreboard class
 */

#ifndef PROJECT1_GAMELIB_SCOREBOARD_H
#define PROJECT1_GAMELIB_SCOREBOARD_H

#include <sstream>

/**
 * Class that keeps track of time spent playing game in seconds
 */
class Scoreboard {
private:
    /// Update time for scoreboard
    double mUpdateTime = -2.5;

    /// Number of seconds for which the game has been played.
    int mSeconds = 0;

    /// Standard string representation of mSeconds
    std::ostringstream mSecondsStream;

public:
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void IncrementSeconds();
    void ResetScoreboard();
    void Update(double elapsed);

    /**
     * Gets number of seconds, used for testing
     * @return number of seconds
     */
    int GetSeconds() const { return mSeconds; };
};

#endif //PROJECT1_GAMELIB_SCOREBOARD_H
