from django.shortcuts import render

# Create your views here.
import joblib
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status

# Load the model
MODEL_PATH = "/home/netprincesingh/crop_predictor/predictor/models/crop_model.joblib"
model = joblib.load(MODEL_PATH)

class CropPredictionAPIView(APIView):
    def post(self, request):
        try:
            # Extract data from request
            data = request.data
            N = data.get("N")
            P = data.get("P")
            K = data.get("K")
            PH = data.get("PH")
            TEMPERATURE = data.get("TEMPERATURE")
            MOISTURIZER = data.get("MOISTURIZER")

            # Validate input
            if None in [N, P, K, PH, TEMPERATURE, MOISTURIZER]:
                return Response({"error": "All fields are required."}, status=status.HTTP_400_BAD_REQUEST)

            # Convert input to the format expected by the model
            input_data = [[N, P, K,TEMPERATURE, MOISTURIZER,PH]]

            # Make prediction
            prediction = model.predict(input_data)[0]

            # Return the prediction
            return Response({"suitable_crop": prediction}, status=status.HTTP_200_OK)

        except Exception as e:
            return Response({"error": str(e)}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
