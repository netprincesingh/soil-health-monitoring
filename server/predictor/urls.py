from django.urls import path
from .views import CropPredictionAPIView

urlpatterns = [
    path('predict/', CropPredictionAPIView.as_view(), name='predict'),
]
