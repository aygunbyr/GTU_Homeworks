from django.urls import path, re_path
from .views import *

app_name = 'trainer'

urlpatterns = [
    path('index/', trainer_index, name='index'),
    re_path(r'^(?P<id>\d+)/$', trainer_detail, name='detail'),
    path('create/', trainer_create, name='create'),
    re_path(r'^(?P<id>[\w-]+)/update/$', trainer_update, name='update'),
    re_path(r'^(?P<id>[\w-]+)/delete/', trainer_delete, name='delete'),
    path('reservation/<int:id>', reservation, name='reservation'),
    path('reservationInfo/<int:id>/<str:date>/', reservationInfo, name='reservationInfo'),
]

