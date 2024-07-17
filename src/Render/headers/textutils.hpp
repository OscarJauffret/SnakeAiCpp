//
// Created by oscar on 17/07/2024.
//

#ifndef SNAKEAI_TEXTUTILS_HPP
#define SNAKEAI_TEXTUTILS_HPP

#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class TextUtils  {
public:
    /**
     * Returns a text object with the specified parameters
     *
     * @param textToWrite The text to write
     * @param charSize The size of the characters
     * @param color The color of the text
     * @param position The position of the text
     * @param font The font
     * @return The text object
     */
    static Text make(const string &textToWrite, int charSize, Color color, Vector2f position, Font &font) {
        Text text;
        text.setFont(font);
        text.setString(textToWrite);
        text.setCharacterSize(charSize);
        text.setFillColor(color);
        text.setPosition(position);
        return text;
    }

    /**
     * Formats a duration in seconds to a string
     * @param seconds The duration formatted as years, days, hours, minutes and seconds
     * @return The formatted string
     */
    static string formatTime(duration_t seconds) {
        const duration_t secondsPerMinute = 60;
        const duration_t secondsPerHour = 60 * secondsPerMinute;
        const duration_t secondsPerDay = 24 * secondsPerHour;
        const duration_t secondsPerYear = 365 * secondsPerDay;

        duration_t years = seconds / secondsPerYear;
        seconds %= secondsPerYear;
        duration_t days = seconds / secondsPerDay;
        seconds %= secondsPerDay;
        duration_t hours = seconds / secondsPerHour;
        seconds %= secondsPerHour;
        duration_t minutes = seconds / secondsPerMinute;
        seconds %= secondsPerMinute;

        string result;
        if (years > 0) result += to_string(years) + " year" + (years > 1 ? "s" : "") + ", ";
        if (days > 0) result += to_string(days) + " day" + (days > 1 ? "s" : "") + ", ";
        if (hours > 0) result += to_string(hours) + " h, ";
        if (minutes > 0) result += to_string(minutes) + " m, ";
        result += to_string(seconds) + " s";

        return result;
    }
};

#endif //SNAKEAI_TEXTUTILS_HPP
