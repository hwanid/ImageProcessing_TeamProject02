
#include "stdafx.h"

int labeling(Mat image, Point biggest, Point smallest)
{
	Mat img = image.clone();

	int answer = 0;
	int num_character = 13;

	stack<Point> stack;

	int flag = 0;
	for (int y = smallest.y; y < biggest.y; y++) {
		for (int x = smallest.x; x < biggest.x; x++) {

			flag = 0;

			Vec3b color = img.at<Vec3b>(Point(x, y));
			int gray = (color.val[0] + color.val[1] + color.val[2]) / 3;

			if (gray < 200 && color.val[0] != num_character && color.val[1] != num_character && color.val[2] != num_character) {
				img.at<Vec3b>(Point(x, y)).val[0] = num_character;
				img.at<Vec3b>(Point(x, y)).val[1] = num_character;
				img.at<Vec3b>(Point(x, y)).val[2] = num_character;

				color = img.at<Vec3b>(Point(x - 1, y));
				gray = (color.val[0] + color.val[1] + color.val[2]) / 3;
				if (gray < 200 && color.val[0] != num_character && color.val[1] != num_character && color.val[2] != num_character) {
					stack.push(Point(x - 1, y));

					img.at<Vec3b>(y, x - 1).val[0] = num_character;
					img.at<Vec3b>(y, x - 1).val[1] = num_character;
					img.at<Vec3b>(y, x - 1).val[2] = num_character;
				}

				color = img.at<Vec3b>(Point(x + 1, y));
				gray = (color.val[0] + color.val[1] + color.val[2]) / 3;
				if (gray < 200 && color.val[0] != num_character && color.val[1] != num_character && color.val[2] != num_character) {
					stack.push(Point(x + 1, y));

					img.at<Vec3b>(y, x + 1)[0] = num_character;
					img.at<Vec3b>(y, x + 1)[1] = num_character;
					img.at<Vec3b>(y, x + 1)[2] = num_character;
				}

				color = img.at<Vec3b>(Point(x, y - 1));
				gray = (color.val[0] + color.val[1] + color.val[2]) / 3;
				if (gray < 200 && color.val[0] != num_character && color.val[1] != num_character && color.val[2] != num_character) {
					stack.push(Point(x, y - 1));

					img.at<Vec3b>(y - 1, x)[0] = num_character;
					img.at<Vec3b>(y - 1, x)[1] = num_character;
					img.at<Vec3b>(y - 1, x)[2] = num_character;
				}

				color = img.at<Vec3b>(Point(x, y + 1));
				gray = (color.val[0] + color.val[1] + color.val[2]) / 3;
				if (gray < 200 && color.val[0] != num_character && color.val[1] != num_character && color.val[2] != num_character) {
					stack.push(Point(x, y + 1));

					img.at<Vec3b>(y + 1, x)[0] = num_character;
					img.at<Vec3b>(y + 1, x)[1] = num_character;
					img.at<Vec3b>(y + 1, x)[2] = num_character;
				}

				while (stack.size() > 0) {
					Point now_point = stack.top();
					stack.pop();

					img.at<Vec3b>(now_point).val[0] = num_character;
					img.at<Vec3b>(now_point).val[1] = num_character;
					img.at<Vec3b>(now_point).val[2] = num_character;

					color = img.at<Vec3b>(Point(now_point.x - 1, now_point.y));
					gray = (color.val[0] + color.val[1] + color.val[2]) / 3;
					if (gray < 200 && color.val[0] != num_character && color.val[1] != num_character && color.val[2] != num_character) {
						stack.push(Point(now_point.x - 1, now_point.y));

						img.at<Vec3b>(Point(now_point.x - 1, now_point.y)).val[0] = num_character;
						img.at<Vec3b>(Point(now_point.x - 1, now_point.y)).val[1] = num_character;
						img.at<Vec3b>(Point(now_point.x - 1, now_point.y)).val[2] = num_character;
					}

					color = img.at<Vec3b>(Point(now_point.x + 1, now_point.y));
					gray = (color.val[0] + color.val[1] + color.val[2]) / 3;
					if (gray < 200 && color.val[0] != num_character && color.val[1] != num_character && color.val[2] != num_character) {
						stack.push(Point(now_point.x + 1, now_point.y));

						img.at<Vec3b>(Point(now_point.x + 1, now_point.y)).val[0] = num_character;
						img.at<Vec3b>(Point(now_point.x + 1, now_point.y)).val[1] = num_character;
						img.at<Vec3b>(Point(now_point.x + 1, now_point.y)).val[2] = num_character;
					}

					color = img.at<Vec3b>(Point(now_point.x, now_point.y - 1));
					gray = (color.val[0] + color.val[1] + color.val[2]) / 3;
					if (gray < 200 && color.val[0] != num_character && color.val[1] != num_character && color.val[2] != num_character) {
						stack.push(Point(now_point.x, now_point.y - 1));

						img.at<Vec3b>(Point(now_point.x, now_point.y - 1)).val[0] = num_character;
						img.at<Vec3b>(Point(now_point.x, now_point.y - 1)).val[1] = num_character;
						img.at<Vec3b>(Point(now_point.x, now_point.y - 1)).val[2] = num_character;
					}

					color = img.at<Vec3b>(Point(now_point.x, now_point.y + 1));
					gray = (color.val[0] + color.val[1] + color.val[2]) / 3;
					if (gray < 200 && color.val[0] != num_character && color.val[1] != num_character && color.val[2] != num_character) {
						stack.push(Point(now_point.x, now_point.y + 1));

						img.at<Vec3b>(Point(now_point.x, now_point.y + 1)).val[0] = num_character;
						img.at<Vec3b>(Point(now_point.x, now_point.y + 1)).val[1] = num_character;
						img.at<Vec3b>(Point(now_point.x, now_point.y + 1)).val[2] = num_character;
					}

					flag = 1;
				}
			}

			if (flag == 1) {
				answer++;
				flag = 0;
			}
		}
	}


	return answer;
}

OneSentence findOneCharacter(Mat image)
{
	OneSentence answer_sentence;

	vector<String> vector_answer;

	vector<Point> vector_smallest_point;
	vector<Point> vector_biggest_point;

	Point smallest_point;
	Point biggest_point;

	biggest_point.x = 0;
	biggest_point.y = 0;

	smallest_point.x = image.cols;
	smallest_point.y = image.rows;

	int row_num = 0;

	int col_num = 0;

	int stepFlag = 0;
	for (int x = 0; x < image.cols; x++) {

		row_num = 0;
		stepFlag = 0;
		for (int y = 0; y < image.rows; y++) {
			Vec3b color = image.at<Vec3b>(Point(x, y));
			int gray = (color.val[0] + color.val[1] + color.val[2]) / 3;

			if (gray < 200) {
				row_num++;
				stepFlag = 1;

				if (smallest_point.x > x) { smallest_point.x = x; }

				if (smallest_point.y > y) { smallest_point.y = y; }

				if (biggest_point.x < x) { biggest_point.x = x; }

				if (biggest_point.y < y) { biggest_point.y = y; }
			}
		}

		if (stepFlag == 0) {
			col_num++;
		}

		if (biggest_point.x != 0 && col_num > (biggest_point.x - smallest_point.x) / 3) {
			/* ¶ç¾î¾²±â */

			Point point;
			point.x = -1;
			point.y = -1;

			vector_smallest_point.push_back(point);
			vector_biggest_point.push_back(point);

			col_num = 0;
		}

		if ((row_num < 5 && row_num > 0) || (biggest_point.x != 0 && stepFlag == 0)) {
			if ((labeling(image, biggest_point, smallest_point) > 1)) {
				Point temp_biggest((smallest_point.x * 2 + biggest_point.x) / 3, biggest_point.y);
				Point temp_smallest((smallest_point.x * 2 + biggest_point.x) / 3, smallest_point.y);

				vector_smallest_point.push_back(smallest_point);
				vector_biggest_point.push_back(temp_biggest);

				vector_smallest_point.push_back(temp_smallest);
				vector_biggest_point.push_back(biggest_point);
			}
			else {
				vector_smallest_point.push_back(smallest_point);
				vector_biggest_point.push_back(biggest_point);
			}

			biggest_point.x = 0;
			biggest_point.y = 0;

			smallest_point.x = image.cols;
			smallest_point.y = image.rows;

			col_num = 0;
		}
	}


	int jump_flag = 0;
	for (int j = 0; j < vector_biggest_point.size(); j++) {
		String answer;

		jump_flag = 0;

		smallest_point = vector_smallest_point[j];
		biggest_point = vector_biggest_point[j];

		if (smallest_point.x == -1) {
			/* ¶ç¾î ¾²±â */

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					answer += "0";
				}
			}

			answer_sentence.vector_character.push_back(answer);
			answer_sentence.vector_row_size.push_back(10);
			answer_sentence.vector_col_size.push_back(10);
		}

		smallest_point.x -= 1;
		smallest_point.y -= 1;

		biggest_point.x += 1;
		biggest_point.y += 1;

		if (biggest_point.x - smallest_point.x < 5 || biggest_point.y - smallest_point.y < 5) {
			jump_flag = 1;
		}

		if (jump_flag == 0) {
			for (int y = smallest_point.y; y < biggest_point.y; y++) {
				for (int x = smallest_point.x; x < biggest_point.x; x++) {

					Vec3b color = image.at<Vec3b>(Point(x, y));
					int gray = (color.val[0] + color.val[1] + color.val[2]) / 3;

					if (gray < 200) {
						answer += "1";
					}
					else {
						answer += "0";
					}
				}

				answer_sentence.vector_character.push_back(answer);
				answer_sentence.vector_row_size.push_back(biggest_point.y - smallest_point.y);
				answer_sentence.vector_col_size.push_back(biggest_point.x - smallest_point.x);
			}
		}
	}

	return answer_sentence;
}
