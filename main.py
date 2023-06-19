import openai
from apikey import api_data 
openai.api_key=api_data #api key, input your own key if you'd like to try this code

import pyttsx3 as tts # text to speech
import speech_recognition as sr # voice recognition from input
import webbrowser  
completion=openai.Completion() # var to ease the customization of AI behavior


# AI responds to the user's question / input
def Reply(question):
    prompt=f'Shawn: {question}\n OpenAi: '
    response = completion.create(prompt=prompt, engine="text-davinci-002", stop=['\Shawn'], max_tokens=200)
    answer = response.choices[0].text.strip()
    return answer

# ---- usage ----

#ans=Reply("What is AI?")
#print(ans)

# ---------------

# defining an "engine" for our tts
engine = tts.init('sapi5')
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[0].id)

# translates the response into a tts
def speak(text):
    engine.say(text)
    engine.runAndWait()

# takes a query, and then return the question based on microphone input (query)
def takeCommand():
    r=sr.Recognizer()
    with sr.Microphone() as source:
        print('Listening...')
        r.pause_threshold = 1
        audio = r.listen(source)
    try:
        print("recognizing...")
        query = r.recognize_google(audio, language='en')
        print("User Said: {} \n".format(query))
    except Exception as e:
        print("Please repeat that again.")
        return "None"
    return query

# ---- DRIVER ---- 
if __name__ == '__main__':
    while True:

        query = takeCommand().lower()
        ans=Reply(query)
        print(ans)
        speak(ans)


        if 'open youtube' in query:
            webbrowser.open("www.youtube.com")
        if 'open google' in query:
            webbrowser.open("www.google.com")
        if 'bye' or 'stop' in query:
            break



