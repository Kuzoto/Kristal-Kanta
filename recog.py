import speech_recognition

recognizer = speech_recognition.Recognizer()
with speech_recognition.Microphone() as source:
    words = recognizer.listen(source)
    if recognizer.recognize_google(words) == "initialize":
        print("Say Something")
        audio = recognizer.listen(source)

print("Google Speech Recognition thinks you said:")
print(recognizer.recognize_google(audio))