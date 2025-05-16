import pandas as pd
import requests

def read_txt(file_path):
    """Reads a .txt file from a given file path."""
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
    return content 

def write_txt(file_path, content):
    """Writes content to a .txt file."""
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(content)  

def read_csv(file_path):
    """Reads a .csv file from a given file path."""
    return pd.read_csv(file_path) 

def write_csv(file_path, data):
    """Writes a DataFrame to a .csv file."""
    data.to_csv(file_path, index=False) 

def read_txt_from_web(url):
    """Reads a .txt file from a URL."""
    response = requests.get(url)
    return response.text if response.status_code == 200 else None

def read_csv_from_web(url):
    """Reads a .csv file from a URL."""
    return pd.read_csv(url)

if __name__ == "__main__":
    txt_content = read_txt("mtcars.txt")
    print(txt_content)

    write_txt("output.txt", "This is a test content.") 

    df = read_csv("mtcars.csv")
    print(df.head())

    write_csv("output.csv", df)

    txt_web_content = read_txt_from_web("https://raw.githubusercontent.com/Jainus/urldata/master/al/abescoldbeer.com.txt")
    print(txt_web_content)

    df_web = read_csv_from_web("https://people.sc.fsu.edu/~jburkardt/data/csv/hw_200.csv")
    print(df_web.head())
