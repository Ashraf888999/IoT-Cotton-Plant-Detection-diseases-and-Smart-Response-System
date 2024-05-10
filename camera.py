import cv2
import numpy as np
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing import image
import pyautogui
import time

# Load your pre-trained CNN model
model = load_model('cotton_disease.h5')

def take_screenshot():
    """Takes a screenshot and saves it to a file."""
    screenshot = pyautogui.screenshot()
    screenshot.save('screenshot.jpg')
    return 'screenshot.jpg'

def predict_disease(image_path):
    """Loads an image, preprocesses it, and uses the model to make predictions."""
    # Load the image
    img = cv2.imread(image_path)

    # Preprocess the image
    img = cv2.resize(img, (256, 256))
    img_array = image.img_to_array(img)
    img_array = np.expand_dims(img_array, axis=0)
    img_array /= 255.0  # Normalize pixel values to be between 0 and 1

    # Make predictions using the model
    predictions = model.predict(img_array)

    # Interpret the results
    predicted_class_index = np.argmax(predictions)
    expected_classes = {
        0: 'bacterial_blight',
        1: 'fussarium_wilt',
        2: 'healthy',
    }

    predicted_class_name = expected_classes.get(predicted_class_index, 'Unknown')
    return predicted_class_name, img

def main():
    while True:
        # Take screenshot every 10 minutes
        image_path = take_screenshot()
        predicted_class_name, img = predict_disease(image_path)
        print(f'Predicted Class: {predicted_class_name}')

        # Display the image with predictions (optional)
        cv2.imshow('Image', img)
        cv2.waitKey(5000)  # Display the image for 5 seconds
        time.sleep(600)  # Wait for 10 minutes

if __name__ == '__main__':
    main()
