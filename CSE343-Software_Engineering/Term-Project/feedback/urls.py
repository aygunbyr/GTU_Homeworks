from django.urls import path, re_path
from .views import *

app_name = 'feedback'

urlpatterns = [
    path('index/', feedback_index, name='index'),
]
