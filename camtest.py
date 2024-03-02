import cv2
import time
import tensorflow as tf
from tensorflow import keras
import numpy as np

def load_model(model_path):
    # Load your pre-trained model
    model = keras.models.load_model(model_path)
    return model

def preprocess_image(img):
    # Preprocess the image based on your model's requirements
    img = cv2.resize(img, (256, 256))
    img = img / 255.0  # Normalize pixel values
    return np.expand_dims(img, axis=0)

def classify_image(model, img):
    preprocessed_image = preprocess_image(img)
    predictions = model.predict(preprocessed_image)
    class_idx = np.argmax(predictions[0])
    return class_idx

def get_class_label(class_idx):
    # Map class indices to human-readable labels
    class_labels = {
        0: 'bacterial_blight',
        1: 'fussarium_wilt',
        2: 'Healthy',
        # Add more labels as needed
    }
    return class_labels.get(class_idx, 'Unknown')

def capture_and_classify_images(model, filename_prefix, capture_interval, quality):
    capture = cv2.VideoCapture(0)  # Open the webcam (0 is the default webcam)

    capture_count = 1
    while True:
        ret, frame = capture.read()

        if not ret:
            print("Failed to capture image")
            break

        filename = f"{filename_prefix}_{capture_count}.jpg"
        cv2.imwrite(filename, frame)

        print(f"Image saved: {filename}")

        # Classify the captured image
        class_idx = classify_image(model, frame)
        class_label = get_class_label(class_idx)
        print(f"Classification result for {filename}: Class {class_idx} - {class_label}")

        capture_count += 1
        time.sleep(capture_interval)

    capture.release()
    cv2.destroyAllWindows()

# Example usage
filename_prefix = 'captured_image'
capture_interval = 5  # seconds
quality = 95  # JPEG image quality (0-100)

# Provide the path to your model
model_path = r'C:\Users\ziady\Desktop\camtest\cotton_disease.h5'

# Load your pre-trained model
model = load_model(model_path)

# Capture and classify images
capture_and_classify_images(model, filename_prefix, capture_interval, quality)
