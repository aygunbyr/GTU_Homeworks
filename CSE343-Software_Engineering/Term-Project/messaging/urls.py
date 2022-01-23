from django.urls import path, re_path
from .views import *

app_name = 'messaging'

urlpatterns = [
    path('index/', message_view, name='index'),
    re_path(r'^(?P<trainer_id>[\w-]+)/send_message/$', send_message_to_trainer, name='send_message'),
]

