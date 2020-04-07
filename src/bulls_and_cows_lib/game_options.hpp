
#pragma once

#include <iostream>

namespace bulls_and_cows {

    struct GameOptions
    {
        unsigned int max_number_of_attempts{4};
        unsigned int number_of_characters_per_code{3};
        char minimum_allowed_character{'A'};
        char maximum_allowed_character{'C'};
    };

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options);

    void display_game_options_menu(std::ostream& output_stream);

    enum class GameOptionsMenuChoice
    {
        Error = -1,
        BackToMain = 0,
        ModifyMaximumNumberOfAttempts = 1,
        ModifyNumberOfCharactersPerCode = 2,
        ModifyMinimumAllowedCharacter = 3,
        ModifyMaximumAllowedCharacter = 4,
        SaveOptions = 5,
        LoadOptions = 6,
    };

    // Ask the user to select an option of the menu
    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream);

    bool save_game_options(std::ostream& output_file_stream, const GameOptions& game_options);

    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options);

    void modify_maximum_number_of_attempts(GameOptions& game_options, std::ostream& output_stream, std::istream& input_stream);

    void modify_number_of_characters_per_code(GameOptions& game_options, std::ostream& output_stream, std::istream& input_stream);

    void modify_minimum_allowed_characters(GameOptions& game_options, std::ostream& output_stream, std::istream& input_stream);

    void modify_maximum_allowed_characters(GameOptions& game_options, std::ostream& output_stream, std::istream& input_stream);

} // namespace bulls_and_cows
