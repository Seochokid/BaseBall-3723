#include <stdexcept>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	explicit Baseball(const string& question) : question(question) {

	}

	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);
		return { isGuessCorrect(guessNumber), getStrikes(guessNumber), getBalls(guessNumber) };
	}

	bool isGuessCorrect(const std::string& guessNumber)
	{
		return guessNumber == question;
	}

	void assertIllegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Must not have the same number");
		}
	}

	bool isDuplicatedNumber(const std::string& guessNumber)
	{
		return guessNumber[0] == guessNumber[1] ||
			guessNumber[0] == guessNumber[2] ||
			guessNumber[1] == guessNumber[2];
	}

	int getStrikes(const string& guessNumber) {
		int strikes = 0;

		for (int i = 0; i < 3; ++i) {
			if (guessNumber[i] == question[i]) {
				strikes++;
			}
		}
		return strikes;
	}

	int getBalls(const string& guessNumber) {
		int balls = 0;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (i != j && guessNumber[i] == question[j]) {
					balls++;
				}
			}
		}
		return balls;
	}

private:
	string question;
};