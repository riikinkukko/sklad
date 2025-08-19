import requests
def get_data_list():
    url = 'https://riikinkukko.pythonanywhere.com/api/data/'
    response = requests.get(url)
    if response.status_code == 200:
        data_list = response.json()
        return data_list
    else:
        print(f"Error: Unable to fetch data. Status code: {response.status_code}")
    return None

data_list =  get_data_list()

while data_list == []:
    data_list = get_data_list()

print(data_list)