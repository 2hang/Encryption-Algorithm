// 대칭키, 스트림 암호

#include <iostream>
#include <Windows.h>
#include <string.h>

using namespace std;

int main() {
	byte S[256]; // 0-255
	byte K[256]; // key 반복
	byte key_streamByte; // key값으로 섞인 배열 S에서 평문과 암호화할 바이트 하나 선택

	char key[256];
	char plainText[256];

	cout << "key string : ";
	cin >> key;
	cout << endl << "plain string : ";
	cin >> plainText;

	int i = 0, j = 0;
	int cnt = 0, t = 0;

	// 초기화
	for (i = 0; i < 256; i++) {
		S[i] = i;
		K[i] = key[i%strlen(key)];
	}

	// 셔플
	for (i = 0; i < 256; i++) {
		j = (j + S[i] + K[i]) % 256;
		swap(S[i], S[j]);
	}
	i = 0;
	j = 0;

	// XOR 연산 (암호화)
	for (cnt = 0; cnt < strlen(plainText); cnt++) {
		i = (i + 1) & 256;
		j = (j + S[i]) % 256;
		swap(S[i], S[j]);

		t = (S[i] + S[j]) % 256;
		key_streamByte = S[t];

		// 암호화
		plainText[cnt] ^= S[key_streamByte];
		// 즉시 복호화
		//plainText[cnt] ^= S[key_streamByte];
	}
	cout << plainText << endl;
	return 0;
}
