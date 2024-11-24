#include "logics.h"

std::string encryption(std::string text, std::string side, int step) {
	char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::string encryptedMessage = "";

	if (side == "right") {
		for (int i = 0; i < text.size(); i++) {
			if (text[i] == ' ' || text[i] == ',') {
				encryptedMessage += text[i];
				continue;
			}

			for (int j = 0; j < 26; j++) {
				if (std::toupper(text[i]) == alphabet[j]) {
					int newIndex = (j + step) % 26;
					encryptedMessage += alphabet[newIndex];
					break;
				}
			}
		}
	}
	else if (side == "left") {
		for (int i = 0; i < text.size(); i++) {
			if (text[i] == ' ' || text[i] == ',') {
				encryptedMessage += text[i];
				continue;
			}

			for (int j = 0; j < 26; j++) {
				if (std::toupper(text[i]) == alphabet[j]) {
					int newIndex = (j - step + 26) % 26;
					encryptedMessage += alphabet[newIndex];
					break;
				}
			}
		}
	}
	else {
		std::cout << "Îøèáêà" << std::endl;
	}

	return encryptedMessage;
}