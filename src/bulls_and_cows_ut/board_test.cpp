
#include <bulls_and_cows_lib/board.hpp>
#include <catch2/catch.hpp>
#include <sstream>

// Examples of unit tests for the functions declared in board.hpp
// These unit tests are disabled because you first need to define the tested functions in board.cpp

TEST_CASE("TEST bulls_and_cows::create_board")
{
    // ARRANGE
    const bulls_and_cows::GameOptions game_options{};

    // ACT
    const bulls_and_cows::Board board = bulls_and_cows::create_board(game_options);

    // ASSERT
    REQUIRE(board.attempts_and_feedbacks.empty());
    REQUIRE(board.secret_code.value.size() == game_options.number_of_characters_per_code);
    for (const char c : board.secret_code.value)
    {
        REQUIRE(c >= game_options.minimum_allowed_character);
        REQUIRE(c <= game_options.maximum_allowed_character);
    }
}

TEST_CASE("TEST bulls_and_cows::validate_attempt WHEN attempt's length is too small")
{
    // ARRANGE
    const bulls_and_cows::GameOptions game_options{};
    const bulls_and_cows::Code attempt{};

    // ACT
    const bool result = bulls_and_cows::validate_attempt(game_options, attempt);

    // ASSERT
    REQUIRE(!result);
}

TEST_CASE("TEST bulls_and_cows::validate_attempt WHEN attempt contains non-allowed characters")
{
    // ARRANGE
    const bulls_and_cows::GameOptions game_options{};
    const bulls_and_cows::Code attempt{"WXYZ"};

    // ACT
    const bool result = bulls_and_cows::validate_attempt(game_options, attempt);

    // ASSERT
    REQUIRE(!result);
}

TEST_CASE("TEST bulls_and_cows::compare_attempt_with_secret_code WHEN 0 bull and 3 cows")
{
    // ARRANGE
    const bulls_and_cows::Code attempt{std::string{"ABCD"}};
    const bulls_and_cows::Code secret{std::string{"DCBE"}};

    // ACT
    const bulls_and_cows::Feedback feedback = bulls_and_cows::compare_attempt_with_secret_code(attempt, secret);

    // ASSERT
    REQUIRE(feedback.bulls == 0);
    REQUIRE(feedback.cows == 3);
}

TEST_CASE("TEST bulls_and_cows::compare_attempt_with_secret_code WHEN 1 bull and 2 cows")
{
    // ARRANGE
    const bulls_and_cows::Code attempt{std::string{"ABCD"}};
    const bulls_and_cows::Code secret{std::string{"ACBE"}};

    // ACT
    const bulls_and_cows::Feedback feedback = bulls_and_cows::compare_attempt_with_secret_code(attempt, secret);

    // ASSERT
    REQUIRE(feedback.bulls == 1);
    REQUIRE(feedback.cows == 2);
}

TEST_CASE("TEST bulls_and_cows::compare_attempt_with_secret_code WHEN 1 bull and 0 cow")  
{
    // ARRANGE
    const bulls_and_cows::Code attempt{std::string{"ABCD"}};
    const bulls_and_cows::Code secret{std::string{"AEFG"}};

    // ACT
    const bulls_and_cows::Feedback feedback = bulls_and_cows::compare_attempt_with_secret_code(attempt, secret);

    // ASSERT
    REQUIRE(feedback.bulls == 1);
    REQUIRE(feedback.cows == 0);
}

TEST_CASE("TEST bulls_and_cows::compare_attempt_with_secret_code WHEN 4 bulls and 0 cow")
{
    // ARRANGE
    const bulls_and_cows::Code attempt{std::string{"ABCD"}};
    const bulls_and_cows::Code secret{std::string{"ABCD"}};

    // ACT
    const bulls_and_cows::Feedback feedback = bulls_and_cows::compare_attempt_with_secret_code(attempt, secret);

    // ASSERT
    REQUIRE(feedback.bulls == 4);
    REQUIRE(feedback.cows == 0);
}


TEST_CASE("TEST bulls_and_cows::compare_attempt_with_secret_code WHEN 0 bulls and 0 cows")
{
    // ARRANGE
    const bulls_and_cows::Code attempt{"ABCD"};
    const bulls_and_cows::Code secret_code{"EFGH"};

    // ACT
    const bulls_and_cows::Feedback feedback = bulls_and_cows::compare_attempt_with_secret_code(attempt, secret_code);

    // ASSERT
    REQUIRE(feedback.bulls == 0);
    REQUIRE(feedback.cows == 0);
}


TEST_CASE("TEST bulls_and_cows::is_end_of_game WHEN not yet the end")
{
    // ARRANGE
    const bulls_and_cows::GameOptions game_options{};
    const bulls_and_cows::Board board{bulls_and_cows::Code{"ABCD"}};

    // ACT
    const bool result = bulls_and_cows::is_end_of_game(game_options, board);

    // ASSERT
    REQUIRE(!result);
}


TEST_CASE("TEST bulls_and_cows::is_win WHEN codebreaker is not yet winning")
{
    // ARRANGE
    const bulls_and_cows::GameOptions game_options{};
    const bulls_and_cows::Board board{bulls_and_cows::Code{"ABCD"}};

    // ACT
    const bool result = bulls_and_cows::is_win(game_options, board);

    // ASSERT
    REQUIRE(!result);
}

TEST_CASE("TEST bulls_and_cows::ask_attempt WHEN attempt is invalid and then is valid")
{
    // ARRANGE
    const bulls_and_cows::GameOptions game_options{};
    const bulls_and_cows::Board board{bulls_and_cows::Code{"DCBA"}};
    std::stringstream output_stream{};
    std::stringstream input_stream{"AB\nABCDE\nABCD"};

    // ASK
    const bulls_and_cows::Code attempt = bulls_and_cows::ask_attempt(output_stream, input_stream, game_options, board);

    // ASSERT
    REQUIRE(attempt.value == "ABCD");
    REQUIRE(output_stream.str() ==
            "What is your guess #01 (4 different characters between 'A' and 'H') : "
            "Your attempt is not valid, try again\n"
            "What is your guess #01 (4 different characters between 'A' and 'H') : "
            "Your attempt is not valid, try again\n"
            "What is your guess #01 (4 different characters between 'A' and 'H') : ");
}

/*
TEST_CASE("TEST bulls_and_cows::display_board WHEN codebreaker has not yet played")
{
    // ARRANGE
    const bulls_and_cows::GameOptions game_options{};
    const bulls_and_cows::Board board{bulls_and_cows::Code{"ABCD"}};
    std::stringstream output_stream{};

    // ACT
    bulls_and_cows::display_board(output_stream, game_options, board);

    // ASSERT
    const std::string output_result = output_stream.str();
    REQUIRE(output_result ==
            "-------------------------------------\n"
            "| SECRET   * * * * * |              |\n"
            "-------------------------------------\n"
            "| ATTEMPTS           | BULLS | COWS |\n"
            "-------------------------------------\n"
            "| #12      . . . . . |       |      |\n"
            "| #11      . . . . . |       |      |\n"
            "| #10      . . . . . |       |      |\n"
            "| #09      . . . . . |       |      |\n"
            "| #08      . . . . . |       |      |\n"
            "| #07      . . . . . |       |      |\n"
            "| #06      . . . . . |       |      |\n"
            "| #05      . . . . . |       |      |\n"
            "| #04      . . . . . |       |      |\n"
            "| #03      . . . . . |       |      |\n"
            "| #02      . . . . . |       |      |\n"
            "| #01      . . . . . |       |      |\n"
            "-------------------------------------\n");
}
*/




