import json
from datetime import datetime
from zhipuai import ZhipuAI

# 创建 ZhipuAI 客户端
# https://www.bigmodel.cn/
client = ZhipuAI(api_key="输入你申请的API")  # 请填写您自己的 APIKey

def read_last_n_lines(file_path, n):
    """
    读取文件的最后 n 行
    """
    with open(file_path, 'r', encoding='utf-8') as file:
        lines = file.readlines()[-n:]
    return [json.loads(line.strip()) for line in lines]

def send_to_ai(messages):
    """
    将对话发送给 AI（小雯）并获取回复
    """
    try:
        # 构造对话历史
        conversation = "\n".join([f"{msg['userId']}: {msg['content']}" for msg in messages])

        # 发送给 AI
        response = client.chat.completions.create(
            model="glm-4-plus",  # 使用 GLM-4 模型
            messages=[
                {
                    "role": "system",
                    "content": "你叫小雯，是一个的女生，喜欢打篮球听音乐读书。\
                    如果有人问你男友是谁你就说是文航，如果没问就不说。\
                    请根据对话历史，用轻松愉快的语气回复，如果需要有哲理则要回复的有意义。"
                },
                {
                    "role": "user",
                    "content": f"这是最近的对话历史：\n{conversation}\n\n请回复："
                }
            ],
        )

        # 提取 AI 的回复
        ai_reply = response.choices[0].message.content.strip()
        return ai_reply

    except Exception as e:
        print(f"发生错误: {e}")
        return None

def append_to_file(file_path, content, user_id="ai-user"):
    """
    将 AI 的回复插入到文件中
    """
    try:
        # 构造新消息
        new_message = {
            "content": content,
            "timestamp": datetime.utcnow().isoformat() + "Z",
            "userId": user_id
        }

        # 写入文件
        with open(file_path, 'a', encoding='utf-8') as file:
            file.write(json.dumps(new_message, ensure_ascii=False) + "\n")

        print(f"已插入 AI 的回复：{content}")

    except Exception as e:
        print(f"写入文件时发生错误: {e}")

def main():
    # 读取最后几行对话
    file_path = "./chatPool/chatPool.db"
    last_10_messages = read_last_n_lines(file_path, 5)

    # 发送给 AI 并获取回复
    ai_reply = send_to_ai(last_10_messages)

    if ai_reply:
        # 将 AI 的回复插入到文件中
        append_to_file(file_path, ai_reply)

if __name__ == "__main__":
    main()